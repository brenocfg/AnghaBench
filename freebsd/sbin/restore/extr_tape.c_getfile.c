#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int c_size; int c_extsize; scalar_t__ c_type; scalar_t__ c_magic; int c_count; scalar_t__* c_addr; } ;

/* Variables and functions */
 scalar_t__ Dflag ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 scalar_t__ GOOD ; 
 int MAXBSIZE ; 
 scalar_t__ MIN (int,int volatile) ; 
 int TP_BSIZE ; 
 int TP_NINDIR ; 
 scalar_t__ TS_ADDR ; 
 scalar_t__ TS_END ; 
 int /*<<< orphan*/  blksread ; 
 TYPE_4__ curfile ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  findinode (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int fssize ; 
 scalar_t__ gethead (TYPE_1__*) ; 
 scalar_t__ gettingfile ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ readmapflag ; 
 int /*<<< orphan*/  readtape (char*) ; 
 int /*<<< orphan*/  restart ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skiphole (void (*) (char*,size_t),size_t*) ; 
 TYPE_1__ spcl ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 void stub1 (char*,size_t) ; 
 void stub2 (char*,size_t) ; 
 void stub3 (char*,size_t) ; 

void
getfile(void (*datafill)(char *, size_t), void (*attrfill)(char *, size_t),
	void (*skip)(char *, size_t))
{
	int i;
	volatile off_t size;
	size_t seekpos;
	int curblk, attrsize;
	void (*fillit)(char *, size_t);
	char buf[MAXBSIZE / TP_BSIZE][TP_BSIZE];
	char junk[TP_BSIZE];

	curblk = 0;
	size = spcl.c_size;
	seekpos = 0;
	attrsize = spcl.c_extsize;
	if (spcl.c_type == TS_END)
		panic("ran off end of tape\n");
	if (spcl.c_magic != FS_UFS2_MAGIC)
		panic("not at beginning of a file\n");
	if (!gettingfile && setjmp(restart) != 0)
		return;
	gettingfile++;
	fillit = datafill;
	if (size == 0 && attrsize > 0) {
		fillit = attrfill;
		size = attrsize;
		attrsize = 0;
	}
loop:
	for (i = 0; i < spcl.c_count; i++) {
		if (!readmapflag && i > TP_NINDIR) {
			if (Dflag) {
				fprintf(stderr, "spcl.c_count = %jd\n",
				    (intmax_t)spcl.c_count);
				break;
			} else
				panic("spcl.c_count = %jd\n",
				    (intmax_t)spcl.c_count);
		}
		if (readmapflag || spcl.c_addr[i]) {
			readtape(&buf[curblk++][0]);
			if (curblk == fssize / TP_BSIZE) {
				skiphole(skip, &seekpos);
				(*fillit)((char *)buf, (long)(size > TP_BSIZE ?
				     fssize : (curblk - 1) * TP_BSIZE + size));
				curblk = 0;
			}
		} else {
			if (curblk > 0) {
				skiphole(skip, &seekpos);
				(*fillit)((char *)buf, (long)(size > TP_BSIZE ?
				     curblk * TP_BSIZE :
				     (curblk - 1) * TP_BSIZE + size));
				curblk = 0;
			}
			/*
			 * We have a block of a hole. Don't skip it
			 * now, because there may be next adjacent
			 * block of the hole in the file. Postpone the
			 * seek until next file write.
			 */
			seekpos += (long)MIN(TP_BSIZE, size);
		}
		if ((size -= TP_BSIZE) <= 0) {
			if (size > -TP_BSIZE && curblk > 0) {
				skiphole(skip, &seekpos);
				(*fillit)((char *)buf,
					(long)((curblk * TP_BSIZE) + size));
				curblk = 0;
			}
			if (attrsize > 0) {
				fillit = attrfill;
				size = attrsize;
				attrsize = 0;
				continue;
			}
			if (spcl.c_count - i > 1)
				dprintf(stdout, "skipping %d junk block(s)\n",
					spcl.c_count - i - 1);
			for (i++; i < spcl.c_count; i++) {
				if (!readmapflag && i > TP_NINDIR) {
					if (Dflag) {
						fprintf(stderr,
						    "spcl.c_count = %jd\n",
						    (intmax_t)spcl.c_count);
						break;
					} else 
						panic("spcl.c_count = %jd\n",
						    (intmax_t)spcl.c_count);
				}
				if (readmapflag || spcl.c_addr[i])
					readtape(junk);
			}
			break;
		}
	}
	if (gethead(&spcl) == GOOD && size > 0) {
		if (spcl.c_type == TS_ADDR)
			goto loop;
		dprintf(stdout,
			"Missing address (header) block for %s at %ld blocks\n",
			curfile.name, blksread);
	}
	if (curblk > 0)
		panic("getfile: lost data\n");
	findinode(&spcl);
	gettingfile = 0;
}