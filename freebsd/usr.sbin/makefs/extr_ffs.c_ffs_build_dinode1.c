#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ufs1_dinode {size_t di_size; int /*<<< orphan*/  di_db; int /*<<< orphan*/  di_rdev; int /*<<< orphan*/  di_ctimensec; int /*<<< orphan*/  di_mtimensec; int /*<<< orphan*/  di_atimensec; int /*<<< orphan*/  di_ctime; int /*<<< orphan*/  di_mtime; int /*<<< orphan*/  di_atime; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; int /*<<< orphan*/  di_gen; int /*<<< orphan*/  di_flags; int /*<<< orphan*/  di_nlink; int /*<<< orphan*/  di_mode; } ;
struct stat {scalar_t__ st_ino; size_t st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_ctimensec; int /*<<< orphan*/  st_mtimensec; int /*<<< orphan*/  st_atimensec; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_flags; int /*<<< orphan*/  st_mode; } ;
struct TYPE_10__ {void* symlink; int /*<<< orphan*/  type; TYPE_1__* inode; } ;
typedef  TYPE_2__ fsnode ;
struct TYPE_11__ {int /*<<< orphan*/  needswap; } ;
typedef  TYPE_3__ fsinfo_t ;
struct TYPE_12__ {size_t size; void* buf; } ;
typedef  TYPE_4__ dirbuf_t ;
struct TYPE_9__ {struct stat st; int /*<<< orphan*/  nlink; } ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 size_t UFS1_MAXSYMLINKLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memset (struct ufs1_dinode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  random () ; 
 struct stat stampst ; 
 size_t strlen (void*) ; 
 int /*<<< orphan*/  ufs_rw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
ffs_build_dinode1(struct ufs1_dinode *dinp, dirbuf_t *dbufp, fsnode *cur,
		 fsnode *root, fsinfo_t *fsopts)
{
	size_t slen;
	void *membuf;
	struct stat *st = stampst.st_ino != 0 ? &stampst : &cur->inode->st;

	memset(dinp, 0, sizeof(*dinp));
	dinp->di_mode = cur->inode->st.st_mode;
	dinp->di_nlink = cur->inode->nlink;
	dinp->di_size = cur->inode->st.st_size;
#if HAVE_STRUCT_STAT_ST_FLAGS
	dinp->di_flags = cur->inode->st.st_flags;
#endif
	dinp->di_gen = random();
	dinp->di_uid = cur->inode->st.st_uid;
	dinp->di_gid = cur->inode->st.st_gid;

	dinp->di_atime = st->st_atime;
	dinp->di_mtime = st->st_mtime;
	dinp->di_ctime = st->st_ctime;
#if HAVE_STRUCT_STAT_ST_MTIMENSEC
	dinp->di_atimensec = st->st_atimensec;
	dinp->di_mtimensec = st->st_mtimensec;
	dinp->di_ctimensec = st->st_ctimensec;
#endif
		/* not set: di_db, di_ib, di_blocks, di_spare */

	membuf = NULL;
	if (cur == root) {			/* "."; write dirbuf */
		membuf = dbufp->buf;
		dinp->di_size = dbufp->size;
	} else if (S_ISBLK(cur->type) || S_ISCHR(cur->type)) {
		dinp->di_size = 0;	/* a device */
		dinp->di_rdev =
		    ufs_rw32(cur->inode->st.st_rdev, fsopts->needswap);
	} else if (S_ISLNK(cur->type)) {	/* symlink */
		slen = strlen(cur->symlink);
		if (slen < UFS1_MAXSYMLINKLEN) {	/* short link */
			memcpy(dinp->di_db, cur->symlink, slen);
		} else
			membuf = cur->symlink;
		dinp->di_size = slen;
	}
	return membuf;
}