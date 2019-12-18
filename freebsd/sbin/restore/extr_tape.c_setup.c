#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union u_spcl {int dummy; } u_spcl ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct stat {int st_blksize; } ;
struct TYPE_10__ {void* action; } ;
struct TYPE_7__ {scalar_t__ c_checksum; int /*<<< orphan*/  c_type; int /*<<< orphan*/  c_magic; } ;
struct TYPE_9__ {TYPE_1__ s_spcl; } ;
struct TYPE_8__ {int c_volume; scalar_t__ c_type; int c_count; int /*<<< orphan*/  c_date; int /*<<< orphan*/  c_ddate; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FLUSHTAPEBUF () ; 
 int /*<<< orphan*/  FS_UFS2_MAGIC ; 
 int MAXBSIZE ; 
 int NBBY ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SETINO (int /*<<< orphan*/ ,char*) ; 
 int TP_BSIZE ; 
 scalar_t__ TS_BITS ; 
 scalar_t__ TS_CLRI ; 
 int /*<<< orphan*/  TS_END ; 
 int /*<<< orphan*/  UFS_WINO ; 
 void* USING ; 
 void* _time64_to_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bflag ; 
 int /*<<< orphan*/  blksread ; 
 char* calloc (unsigned int,unsigned int) ; 
 char command ; 
 TYPE_6__ curfile ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* dumpdate ; 
 char* dumpmap ; 
 void* dumptime ; 
 TYPE_5__ endoftapemark ; 
 int /*<<< orphan*/  errno ; 
 int fileno (scalar_t__) ; 
 int /*<<< orphan*/  findinode (TYPE_2__*) ; 
 int /*<<< orphan*/  findtapeblksize () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fssize ; 
 int /*<<< orphan*/  getfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gethead (TYPE_2__*) ; 
 scalar_t__ host ; 
 scalar_t__ howmany (int,int) ; 
 char* magtape ; 
 char* map ; 
 int maxino ; 
 int mt ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pipecmdin ; 
 scalar_t__ pipein ; 
 scalar_t__ popen (char*,char*) ; 
 scalar_t__ popenfp ; 
 int /*<<< orphan*/  printdumpinfo () ; 
 int rmtopen (char*,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  setdumpnum () ; 
 int setenv (char*,char*,int) ; 
 TYPE_2__ spcl ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int tapesread ; 
 char* usedinomap ; 
 scalar_t__ vflag ; 
 int volno ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xtrmap ; 
 int /*<<< orphan*/  xtrmapskip ; 

void
setup(void)
{
	int i, j, *ip;
	struct stat stbuf;

	vprintf(stdout, "Verify tape and initialize maps\n");
	if (pipecmdin) {
		if (setenv("RESTORE_VOLUME", "1", 1) == -1) {
			fprintf(stderr, "Cannot set $RESTORE_VOLUME: %s\n",
			    strerror(errno));
			done(1);
		}
		popenfp = popen(magtape, "r");
		mt = popenfp ? fileno(popenfp) : -1;
	} else
#ifdef RRESTORE
	if (host)
		mt = rmtopen(magtape, 0);
	else
#endif
	if (pipein)
		mt = 0;
	else
		mt = open(magtape, O_RDONLY, 0);
	if (mt < 0) {
		fprintf(stderr, "%s: %s\n", magtape, strerror(errno));
		done(1);
	}
	volno = 1;
	setdumpnum();
	FLUSHTAPEBUF();
	if (!pipein && !pipecmdin && !bflag)
		findtapeblksize();
	if (gethead(&spcl) == FAIL) {
		fprintf(stderr, "Tape is not a dump tape\n");
		done(1);
	}
	if (pipein) {
		endoftapemark.s_spcl.c_magic = FS_UFS2_MAGIC;
		endoftapemark.s_spcl.c_type = TS_END;
		ip = (int *)&endoftapemark;
		j = sizeof(union u_spcl) / sizeof(int);
		i = 0;
		do
			i += *ip++;
		while (--j);
		endoftapemark.s_spcl.c_checksum = CHECKSUM - i;
	}
	if (vflag || command == 't')
		printdumpinfo();
	dumptime = _time64_to_time(spcl.c_ddate);
	dumpdate = _time64_to_time(spcl.c_date);
	if (stat(".", &stbuf) < 0) {
		fprintf(stderr, "cannot stat .: %s\n", strerror(errno));
		done(1);
	}
	if (stbuf.st_blksize > 0 && stbuf.st_blksize < TP_BSIZE )
		fssize = TP_BSIZE;
	if (stbuf.st_blksize >= TP_BSIZE && stbuf.st_blksize <= MAXBSIZE)
		fssize = stbuf.st_blksize;
	if (((TP_BSIZE - 1) & stbuf.st_blksize) != 0) {
		fprintf(stderr, "Warning: filesystem with non-multiple-of-%d "
		    "blocksize (%d);\n", TP_BSIZE, stbuf.st_blksize);
		fssize = roundup(fssize, TP_BSIZE);
		fprintf(stderr, "\twriting using blocksize %ld\n", fssize);
	}
	if (spcl.c_volume != 1) {
		fprintf(stderr, "Tape is not volume 1 of the dump\n");
		done(1);
	}
	if (gethead(&spcl) == FAIL) {
		dprintf(stdout, "header read failed at %ld blocks\n", blksread);
		panic("no header after volume mark!\n");
	}
	findinode(&spcl);
	if (spcl.c_type != TS_CLRI) {
		fprintf(stderr, "Cannot find file removal list\n");
		done(1);
	}
	maxino = (spcl.c_count * TP_BSIZE * NBBY) + 1;
	dprintf(stdout, "maxino = %ju\n", (uintmax_t)maxino);
	map = calloc((unsigned)1, (unsigned)howmany(maxino, NBBY));
	if (map == NULL)
		panic("no memory for active inode map\n");
	usedinomap = map;
	curfile.action = USING;
	getfile(xtrmap, xtrmapskip, xtrmapskip);
	if (spcl.c_type != TS_BITS) {
		fprintf(stderr, "Cannot find file dump list\n");
		done(1);
	}
	map = calloc((unsigned)1, (unsigned)howmany(maxino, NBBY));
	if (map == (char *)NULL)
		panic("no memory for file dump list\n");
	dumpmap = map;
	curfile.action = USING;
	getfile(xtrmap, xtrmapskip, xtrmapskip);
	/*
	 * If there may be whiteout entries on the tape, pretend that the
	 * whiteout inode exists, so that the whiteout entries can be
	 * extracted.
	 */
	SETINO(UFS_WINO, dumpmap);
	/* 'r' restores don't call getvol() for tape 1, so mark it as read. */
	if (command == 'r')
		tapesread = 1;
}