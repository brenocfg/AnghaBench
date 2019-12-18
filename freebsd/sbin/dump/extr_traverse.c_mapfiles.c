#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int u_char ;
struct cg {int cg_initediblk; } ;
typedef  int ino_t ;
struct TYPE_4__ {int fs_ncg; int fs_ipg; scalar_t__ fs_magic; int fs_flags; int /*<<< orphan*/  fs_cgsize; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  CLRINO (int,int /*<<< orphan*/ ) ; 
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int FS_DOSOFTDEP ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 int IFDIR ; 
 int IFLNK ; 
 int IFMT ; 
 int IFREG ; 
 int /*<<< orphan*/  SETINO (int,int /*<<< orphan*/ ) ; 
 int UFS_ROOTINO ; 
 int UF_NODUMP ; 
 scalar_t__ WANTTODUMP (union dinode*) ; 
 int /*<<< orphan*/  blkread (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ blockest (union dinode*) ; 
 int /*<<< orphan*/  cg_chkmagic (struct cg*) ; 
 int* cg_inosused (struct cg*) ; 
 int /*<<< orphan*/  cgtod (TYPE_1__*,int) ; 
 int /*<<< orphan*/  di_flags ; 
 int /*<<< orphan*/  dumpdirmap ; 
 int /*<<< orphan*/  dumpinomap ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 union dinode* getino (int,int*) ; 
 struct cg* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonodump ; 
 int /*<<< orphan*/  quit (char*,...) ; 
 TYPE_1__* sblock ; 
 int /*<<< orphan*/  usedinomap ; 

int
mapfiles(ino_t maxino, long *tapesize)
{
	int i, cg, mode, inosused;
	int anydirskipped = 0;
	union dinode *dp;
	struct cg *cgp;
	ino_t ino;
	u_char *cp;

	if ((cgp = malloc(sblock->fs_cgsize)) == NULL)
		quit("mapfiles: cannot allocate memory.\n");
	for (cg = 0; cg < sblock->fs_ncg; cg++) {
		ino = cg * sblock->fs_ipg;
		blkread(fsbtodb(sblock, cgtod(sblock, cg)), (char *)cgp,
		    sblock->fs_cgsize);
		if (sblock->fs_magic == FS_UFS2_MAGIC)
			inosused = cgp->cg_initediblk;
		else
			inosused = sblock->fs_ipg;
		/*
		 * If we are using soft updates, then we can trust the
		 * cylinder group inode allocation maps to tell us which
		 * inodes are allocated. We will scan the used inode map
		 * to find the inodes that are really in use, and then
		 * read only those inodes in from disk.
		 */
		if (sblock->fs_flags & FS_DOSOFTDEP) {
			if (!cg_chkmagic(cgp))
				quit("mapfiles: cg %d: bad magic number\n", cg);
			cp = &cg_inosused(cgp)[(inosused - 1) / CHAR_BIT];
			for ( ; inosused > 0; inosused -= CHAR_BIT, cp--) {
				if (*cp == 0)
					continue;
				for (i = 1 << (CHAR_BIT - 1); i > 0; i >>= 1) {
					if (*cp & i)
						break;
					inosused--;
				}
				break;
			}
			if (inosused <= 0)
				continue;
		}
		for (i = 0; i < inosused; i++, ino++) {
			if (ino < UFS_ROOTINO ||
			    (dp = getino(ino, &mode)) == NULL ||
			    (mode & IFMT) == 0)
				continue;
			if (ino >= maxino) {
				msg("Skipping inode %ju >= maxino %ju\n",
				    (uintmax_t)ino, (uintmax_t)maxino);
				continue;
			}
			/*
			 * Everything must go in usedinomap so that a check
			 * for "in dumpdirmap but not in usedinomap" to detect
			 * dirs with nodump set has a chance of succeeding
			 * (this is used in mapdirs()).
			 */
			SETINO(ino, usedinomap);
			if (mode == IFDIR)
				SETINO(ino, dumpdirmap);
			if (WANTTODUMP(dp)) {
				SETINO(ino, dumpinomap);
				if (mode != IFREG &&
				    mode != IFDIR &&
				    mode != IFLNK)
					*tapesize += 1;
				else
					*tapesize += blockest(dp);
				continue;
			}
			if (mode == IFDIR) {
				if (!nonodump &&
				    (DIP(dp, di_flags) & UF_NODUMP))
					CLRINO(ino, usedinomap);
				anydirskipped = 1;
			}
		}
	}
	/*
	 * Restore gets very upset if the root is not dumped,
	 * so ensure that it always is dumped.
	 */
	SETINO(UFS_ROOTINO, dumpinomap);
	return (anydirskipped);
}