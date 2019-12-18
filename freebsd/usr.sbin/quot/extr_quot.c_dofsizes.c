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
typedef  union dinode {int dummy; } dinode ;
struct fsizes {int* fsz_sz; int fsz_last; int fsz_first; scalar_t__* fsz_count; struct fsizes* fsz_next; } ;
struct fs {int fs_ncg; int fs_ipg; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int ino_t ;
typedef  int daddr_t ;

/* Variables and functions */
 int DIP (struct fs*,union dinode*,int /*<<< orphan*/ ) ; 
 int FSZCNT ; 
 int IFDIR ; 
 int IFMT ; 
 int IFREG ; 
 int SIZE (int) ; 
 int actualblocks (struct fs*,union dinode*) ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ estimate ; 
 struct fsizes* fsizes ; 
 union dinode* get_inode (int,struct fs*,int) ; 
 int /*<<< orphan*/  isfree (struct fs*,union dinode*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rounddown (int,int) ; 
 int virtualblocks (struct fs*,union dinode*) ; 

__attribute__((used)) static void
dofsizes(int fd, struct fs *super, char *name)
{
	ino_t inode, maxino;
	union dinode *dp;
	daddr_t sz, ksz;
	struct fsizes *fp, **fsp;
	int i;

	maxino = super->fs_ncg * super->fs_ipg - 1;
#ifdef	COMPAT
	if (!(fsizes = (struct fsizes *)malloc(sizeof(struct fsizes))))
		errx(1, "allocate fsize structure");
#endif	/* COMPAT */
	for (inode = 0; inode < maxino; inode++) {
		errno = 0;
		if ((dp = get_inode(fd,super,inode))
#ifdef	COMPAT
		    && ((DIP(super, dp, di_mode) & IFMT) == IFREG
			|| (DIP(super, dp, di_mode) & IFMT) == IFDIR)
#else	/* COMPAT */
		    && !isfree(super, dp)
#endif	/* COMPAT */
		    ) {
			sz = estimate ? virtualblocks(super, dp) :
			    actualblocks(super, dp);
#ifdef	COMPAT
			if (sz >= FSZCNT) {
				fsizes->fsz_count[FSZCNT-1]++;
				fsizes->fsz_sz[FSZCNT-1] += sz;
			} else {
				fsizes->fsz_count[sz]++;
				fsizes->fsz_sz[sz] += sz;
			}
#else	/* COMPAT */
			ksz = SIZE(sz);
			for (fsp = &fsizes; (fp = *fsp); fsp = &fp->fsz_next) {
				if (ksz < fp->fsz_last)
					break;
			}
			if (!fp || ksz < fp->fsz_first) {
				if (!(fp = (struct fsizes *)
				    malloc(sizeof(struct fsizes))))
					errx(1, "allocate fsize structure");
				fp->fsz_next = *fsp;
				*fsp = fp;
				fp->fsz_first = rounddown(ksz, FSZCNT);
				fp->fsz_last = fp->fsz_first + FSZCNT;
				for (i = FSZCNT; --i >= 0;) {
					fp->fsz_count[i] = 0;
					fp->fsz_sz[i] = 0;
				}
			}
			fp->fsz_count[ksz % FSZCNT]++;
			fp->fsz_sz[ksz % FSZCNT] += sz;
#endif	/* COMPAT */
		} else if (errno) {
			err(1, "%s", name);
		}
	}
	sz = 0;
	for (fp = fsizes; fp; fp = fp->fsz_next) {
		for (i = 0; i < FSZCNT; i++) {
			if (fp->fsz_count[i])
				printf("%jd\t%jd\t%d\n",
				    (intmax_t)(fp->fsz_first + i),
				    (intmax_t)fp->fsz_count[i],
				    SIZE(sz += fp->fsz_sz[i]));
		}
	}
}