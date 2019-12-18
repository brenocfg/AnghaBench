#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_long ;
struct vnode {int dummy; } ;
struct msdosfsmount {scalar_t__ pm_rootdirblk; int pm_rootdirsize; scalar_t__ pm_bpcluster; } ;
struct direntry {int dummy; } ;
struct denode {int de_refcnt; int de_Attributes; scalar_t__ de_StartCluster; int de_FileSize; int de_CTime; int de_CDate; int de_ADate; int de_MTime; int de_MDate; int /*<<< orphan*/ * de_Name; scalar_t__ de_CHun; scalar_t__ de_LowerCase; struct vnode* de_vnode; struct msdosfsmount* de_pmp; scalar_t__ de_inode; scalar_t__ de_diroffset; scalar_t__ de_dirclust; scalar_t__ de_flag; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int DD_DAY_SHIFT ; 
 int DD_MONTH_SHIFT ; 
 int DD_YEAR_SHIFT ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DE_INTERNALIZE (struct denode*,struct direntry*) ; 
 int E2BIG ; 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
 scalar_t__ MSDOSFSROOT ; 
 scalar_t__ MSDOSFSROOT_OFS ; 
 int /*<<< orphan*/  MSDOSFS_DPRINTF (char*) ; 
 int /*<<< orphan*/  SLOT_DELETED ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int de_cn2off (struct msdosfsmount*,scalar_t__) ; 
 struct denode* ecalloc (int,int) ; 
 int /*<<< orphan*/  fc_purge (struct denode*,int /*<<< orphan*/ ) ; 
 int pcbmap (struct denode*,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int readep (struct msdosfsmount*,scalar_t__,scalar_t__,struct buf**,struct direntry**) ; 

int
deget(struct msdosfsmount *pmp, u_long dirclust, u_long diroffset,
    struct denode **depp)
{
	int error;
	uint64_t inode;
	struct direntry *direntptr;
	struct denode *ldep;
	struct buf *bp;

	MSDOSFS_DPRINTF(("deget(pmp %p, dirclust %lu, diroffset %lx, depp %p)\n",
	    pmp, dirclust, diroffset, depp));

	/*
	 * On FAT32 filesystems, root is a (more or less) normal
	 * directory
	 */
	if (FAT32(pmp) && dirclust == MSDOSFSROOT)
		dirclust = pmp->pm_rootdirblk;

	inode = (uint64_t)pmp->pm_bpcluster * dirclust + diroffset;

	ldep = ecalloc(1, sizeof(*ldep));
	ldep->de_vnode = NULL;
	ldep->de_flag = 0;
	ldep->de_dirclust = dirclust;
	ldep->de_diroffset = diroffset;
	ldep->de_inode = inode;
	ldep->de_pmp = pmp;
	ldep->de_refcnt = 1;
	fc_purge(ldep, 0);	/* init the FAT cache for this denode */
	/*
	 * Copy the directory entry into the denode area of the vnode.
	 */
	if ((dirclust == MSDOSFSROOT
	     || (FAT32(pmp) && dirclust == pmp->pm_rootdirblk))
	    && diroffset == MSDOSFSROOT_OFS) {
		/*
		 * Directory entry for the root directory. There isn't one,
		 * so we manufacture one. We should probably rummage
		 * through the root directory and find a label entry (if it
		 * exists), and then use the time and date from that entry
		 * as the time and date for the root denode.
		 */
		ldep->de_vnode = (struct vnode *)-1;

		ldep->de_Attributes = ATTR_DIRECTORY;
		ldep->de_LowerCase = 0;
		if (FAT32(pmp))
			ldep->de_StartCluster = pmp->pm_rootdirblk;
			/* de_FileSize will be filled in further down */
		else {
			ldep->de_StartCluster = MSDOSFSROOT;
			ldep->de_FileSize = pmp->pm_rootdirsize * DEV_BSIZE;
		}
		/*
		 * fill in time and date so that dos2unixtime() doesn't
		 * spit up when called from msdosfs_getattr() with root
		 * denode
		 */
		ldep->de_CHun = 0;
		ldep->de_CTime = 0x0000;	/* 00:00:00	 */
		ldep->de_CDate = (0 << DD_YEAR_SHIFT) | (1 << DD_MONTH_SHIFT)
		    | (1 << DD_DAY_SHIFT);
		/* Jan 1, 1980	 */
		ldep->de_ADate = ldep->de_CDate;
		ldep->de_MTime = ldep->de_CTime;
		ldep->de_MDate = ldep->de_CDate;
		/* leave the other fields as garbage */
	} else {
		error = readep(pmp, dirclust, diroffset, &bp, &direntptr);
		if (error) {
			ldep->de_Name[0] = SLOT_DELETED;

			*depp = NULL;
			return (error);
		}
		(void)DE_INTERNALIZE(ldep, direntptr);
		brelse(bp);
	}

	/*
	 * Fill in a few fields of the vnode and finish filling in the
	 * denode.  Then return the address of the found denode.
	 */
	if (ldep->de_Attributes & ATTR_DIRECTORY) {
		/*
		 * Since DOS directory entries that describe directories
		 * have 0 in the filesize field, we take this opportunity
		 * to find out the length of the directory and plug it into
		 * the denode structure.
		 */
		u_long size;

		/*
		 * XXX it sometimes happens that the "." entry has cluster
		 * number 0 when it shouldn't.  Use the actual cluster number
		 * instead of what is written in directory entry.
		 */
		if (diroffset == 0 && ldep->de_StartCluster != dirclust) {
			MSDOSFS_DPRINTF(("deget(): \".\" entry at clust %lu != %lu\n",
			    dirclust, ldep->de_StartCluster));

			ldep->de_StartCluster = dirclust;
		}

		if (ldep->de_StartCluster != MSDOSFSROOT) {
			error = pcbmap(ldep, 0xffff, 0, &size, 0);
			if (error == E2BIG) {
				ldep->de_FileSize = de_cn2off(pmp, size);
				error = 0;
			} else {
				MSDOSFS_DPRINTF(("deget(): pcbmap returned %d\n",
				    error));
			}
		}
	}
	*depp = ldep;
	return (0);
}