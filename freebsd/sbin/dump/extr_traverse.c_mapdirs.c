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
union dinode {int /*<<< orphan*/  dp2; int /*<<< orphan*/  dp1; } ;
typedef  int ino_t ;
struct TYPE_3__ {scalar_t__ fs_magic; scalar_t__ fs_bsize; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  CLRINO (int,char*) ; 
 scalar_t__ DIP (union dinode*,int /*<<< orphan*/ ) ; 
 scalar_t__ FS_UFS1_MAGIC ; 
 int HASDUMPEDFILE ; 
 int HASSUBDIRS ; 
 int /*<<< orphan*/  SETINO (int,int /*<<< orphan*/ ) ; 
 scalar_t__ TSTINO (int,int /*<<< orphan*/ ) ; 
 int UFS_NDADDR ; 
 int UFS_NIADDR ; 
 scalar_t__ blockest (union dinode*) ; 
 int /*<<< orphan*/ * di_db ; 
 int /*<<< orphan*/ * di_ib ; 
 int /*<<< orphan*/  di_size ; 
 int dirindir (int,scalar_t__,int,long*,long*,int,int) ; 
 char* dumpdirmap ; 
 int /*<<< orphan*/  dumpinomap ; 
 union dinode* getino (int,int*) ; 
 int /*<<< orphan*/  nonodump ; 
 scalar_t__ sblksize (TYPE_1__*,scalar_t__,int) ; 
 TYPE_1__* sblock ; 
 int searchdir (int,scalar_t__,long,long,long*,int,int) ; 
 int /*<<< orphan*/  usedinomap ; 

int
mapdirs(ino_t maxino, long *tapesize)
{
	union dinode *dp;
	int i, isdir, nodump;
	char *map;
	ino_t ino;
	union dinode di;
	long filesize;
	int ret, change = 0;

	isdir = 0;		/* XXX just to get gcc to shut up */
	for (map = dumpdirmap, ino = 1; ino < maxino; ino++) {
		if (((ino - 1) % CHAR_BIT) == 0)	/* map is offset by 1 */
			isdir = *map++;
		else
			isdir >>= 1;
		/*
		 * If a directory has been removed from usedinomap, it
		 * either has the nodump flag set, or has inherited
		 * it.  Although a directory can't be in dumpinomap if
		 * it isn't in usedinomap, we have to go through it to
		 * propagate the nodump flag.
		 */
		nodump = !nonodump && (TSTINO(ino, usedinomap) == 0);
		if ((isdir & 1) == 0 || (TSTINO(ino, dumpinomap) && !nodump))
			continue;
		dp = getino(ino, &i);
		/*
		 * inode buf may change in searchdir().
		 */
		if (sblock->fs_magic == FS_UFS1_MAGIC)
			di.dp1 = dp->dp1;
		else
			di.dp2 = dp->dp2;
		filesize = DIP(&di, di_size);
		for (ret = 0, i = 0; filesize > 0 && i < UFS_NDADDR; i++) {
			if (DIP(&di, di_db[i]) != 0)
				ret |= searchdir(ino, DIP(&di, di_db[i]),
				    (long)sblksize(sblock, DIP(&di, di_size),
				    i), filesize, tapesize, nodump, maxino);
			if (ret & HASDUMPEDFILE)
				filesize = 0;
			else
				filesize -= sblock->fs_bsize;
		}
		for (i = 0; filesize > 0 && i < UFS_NIADDR; i++) {
			if (DIP(&di, di_ib[i]) == 0)
				continue;
			ret |= dirindir(ino, DIP(&di, di_ib[i]), i, &filesize,
			    tapesize, nodump, maxino);
		}
		if (ret & HASDUMPEDFILE) {
			SETINO(ino, dumpinomap);
			*tapesize += blockest(&di);
			change = 1;
			continue;
		}
		if (nodump) {
			if (ret & HASSUBDIRS)
				change = 1;	/* subdirs inherit nodump */
			CLRINO(ino, dumpdirmap);
		} else if ((ret & HASSUBDIRS) == 0)
			if (!TSTINO(ino, dumpinomap)) {
				CLRINO(ino, dumpdirmap);
				change = 1;
			}
	}
	return (change);
}