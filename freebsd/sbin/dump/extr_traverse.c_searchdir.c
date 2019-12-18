#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct direct {scalar_t__ d_reclen; scalar_t__ d_ino; char* d_name; } ;
typedef  scalar_t__ ino_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs_bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRINO (scalar_t__,int /*<<< orphan*/ ) ; 
 long HASDUMPEDFILE ; 
 long HASSUBDIRS ; 
 int IFDIR ; 
 int /*<<< orphan*/  SETINO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ blockest (union dinode*) ; 
 int /*<<< orphan*/  dumpdirmap ; 
 int /*<<< orphan*/  dumpinomap ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 union dinode* getino (scalar_t__,int*) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  quit (char*) ; 
 TYPE_1__* sblock ; 
 int /*<<< orphan*/  usedinomap ; 

__attribute__((used)) static int
searchdir(
	ino_t ino,
	ufs2_daddr_t blkno,
	long size,
	long filesize, 
	long *tapesize,
	int nodump,
	ino_t maxino)
{
	int mode;
	struct direct *dp;
	union dinode *ip;
	long loc, ret = 0;
	static caddr_t dblk;

	if (dblk == NULL && (dblk = malloc(sblock->fs_bsize)) == NULL)
		quit("searchdir: cannot allocate indirect memory.\n");
	blkread(fsbtodb(sblock, blkno), dblk, (int)size);
	if (filesize < size)
		size = filesize;
	for (loc = 0; loc < size; ) {
		dp = (struct direct *)(dblk + loc);
		if (dp->d_reclen == 0) {
			msg("corrupted directory, inumber %ju\n",
			    (uintmax_t)ino);
			break;
		}
		loc += dp->d_reclen;
		if (dp->d_ino == 0)
			continue;
		if (dp->d_ino >= maxino) {
			msg("corrupted directory entry, d_ino %ju >= %ju\n",
			    (uintmax_t)dp->d_ino, (uintmax_t)maxino);
			break;
		}
		if (dp->d_name[0] == '.') {
			if (dp->d_name[1] == '\0')
				continue;
			if (dp->d_name[1] == '.' && dp->d_name[2] == '\0')
				continue;
		}
		if (nodump) {
			ip = getino(dp->d_ino, &mode);
			if (TSTINO(dp->d_ino, dumpinomap)) {
				CLRINO(dp->d_ino, dumpinomap);
				*tapesize -= blockest(ip);
			}
			/*
			 * Add back to dumpdirmap and remove from usedinomap
			 * to propagate nodump.
			 */
			if (mode == IFDIR) {
				SETINO(dp->d_ino, dumpdirmap);
				CLRINO(dp->d_ino, usedinomap);
				ret |= HASSUBDIRS;
			}
		} else {
			if (TSTINO(dp->d_ino, dumpinomap)) {
				ret |= HASDUMPEDFILE;
				if (ret & HASSUBDIRS)
					break;
			}
			if (TSTINO(dp->d_ino, dumpdirmap)) {
				ret |= HASSUBDIRS;
				if (ret & HASDUMPEDFILE)
					break;
			}
		}
	}
	return (ret);
}