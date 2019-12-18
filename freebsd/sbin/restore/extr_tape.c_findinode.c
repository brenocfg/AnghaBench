#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct s_spcl {int c_type; long c_count; int /*<<< orphan*/  c_date; scalar_t__ c_inumber; int /*<<< orphan*/  c_size; int /*<<< orphan*/  c_extsize; int /*<<< orphan*/  c_birthtimensec; int /*<<< orphan*/  c_birthtime; int /*<<< orphan*/  c_mtimensec; int /*<<< orphan*/  c_mtime; int /*<<< orphan*/  c_atimensec; int /*<<< orphan*/  c_atime; int /*<<< orphan*/  c_rdev; int /*<<< orphan*/  c_file_flags; int /*<<< orphan*/  c_gid; int /*<<< orphan*/  c_uid; scalar_t__ c_mode; int /*<<< orphan*/ * c_addr; } ;
struct TYPE_4__ {char* name; scalar_t__ ino; int /*<<< orphan*/  size; int /*<<< orphan*/  extsize; int /*<<< orphan*/  birthtime_nsec; int /*<<< orphan*/  birthtime_sec; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime_sec; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime_sec; int /*<<< orphan*/  rdev; int /*<<< orphan*/  file_flags; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; scalar_t__ mode; int /*<<< orphan*/  action; } ;
struct TYPE_3__ {int c_type; } ;

/* Variables and functions */
 scalar_t__ Dflag ; 
 int /*<<< orphan*/  FAIL ; 
 int TP_BSIZE ; 
#define  TS_ADDR 133 
#define  TS_BITS 132 
#define  TS_CLRI 131 
#define  TS_END 130 
#define  TS_INODE 129 
#define  TS_TAPE 128 
 int /*<<< orphan*/  UNKNOWN ; 
 int /*<<< orphan*/  _time64_to_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkcnt ; 
 int /*<<< orphan*/  blksread ; 
 int byteslide ; 
 TYPE_2__ curfile ; 
 int /*<<< orphan*/  dumpdate ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gethead (struct s_spcl*) ; 
 int /*<<< orphan*/  getvol (int /*<<< orphan*/ ) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  readtape (char*) ; 
 TYPE_1__ spcl ; 
 int /*<<< orphan*/  stderr ; 
 int tapesread ; 

__attribute__((used)) static void
findinode(struct s_spcl *header)
{
	static long skipcnt = 0;
	long i;
	char buf[TP_BSIZE];
	int htype;

	curfile.name = "<name unknown>";
	curfile.action = UNKNOWN;
	curfile.mode = 0;
	curfile.ino = 0;
	do {
		htype = header->c_type;
		switch (htype) {

		case TS_ADDR:
			/*
			 * Skip up to the beginning of the next record
			 */
			for (i = 0; i < header->c_count; i++)
				if (header->c_addr[i])
					readtape(buf);
			while (gethead(header) == FAIL ||
			    _time64_to_time(header->c_date) != dumpdate) {
				skipcnt++;
				if (Dflag) {
					byteslide++;
					if (byteslide < TP_BSIZE) {
						blkcnt--;
						blksread--;
					} else 
						byteslide = 0;
				}
			}
			break;

		case TS_INODE:
			curfile.mode = header->c_mode;
			curfile.uid = header->c_uid;
			curfile.gid = header->c_gid;
			curfile.file_flags = header->c_file_flags;
			curfile.rdev = header->c_rdev;
			curfile.atime_sec = header->c_atime;
			curfile.atime_nsec = header->c_atimensec;
			curfile.mtime_sec = header->c_mtime;
			curfile.mtime_nsec = header->c_mtimensec;
			curfile.birthtime_sec = header->c_birthtime;
			curfile.birthtime_nsec = header->c_birthtimensec;
			curfile.extsize = header->c_extsize;
			curfile.size = header->c_size;
			curfile.ino = header->c_inumber;
			break;

		case TS_END:
			/* If we missed some tapes, get another volume. */
			if (tapesread & (tapesread + 1)) {
				getvol(0);
				continue;
			}
			curfile.ino = maxino;
			break;

		case TS_CLRI:
			curfile.name = "<file removal list>";
			break;

		case TS_BITS:
			curfile.name = "<file dump list>";
			break;

		case TS_TAPE:
			if (Dflag)
				fprintf(stderr, "unexpected tape header\n");
			else
				panic("unexpected tape header\n");

		default:
			if (Dflag)
				fprintf(stderr, "unknown tape header type %d\n",
				    spcl.c_type);
			else
				panic("unknown tape header type %d\n",
				    spcl.c_type);
			while (gethead(header) == FAIL ||
			    _time64_to_time(header->c_date) != dumpdate) {
				skipcnt++;
				if (Dflag) {
					byteslide++;
					if (byteslide < TP_BSIZE) {
						blkcnt--;
						blksread--;
					} else 
						byteslide = 0;
				}
			}

		}
	} while (htype == TS_ADDR);
	if (skipcnt > 0)
		fprintf(stderr, "resync restore, skipped %ld %s\n",
		    skipcnt, Dflag ? "bytes" : "blocks");
	skipcnt = 0;
}