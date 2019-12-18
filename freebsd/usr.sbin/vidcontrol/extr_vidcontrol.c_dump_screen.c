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
struct TYPE_4__ {int size; int xsize; int mv_csz; int ysize; int mv_rsz; int* buf; scalar_t__ mv_hsz; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ vid_info_t ;
typedef  int u_int16_t ;
typedef  TYPE_1__ scrshot_t ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_GETINFO ; 
 int /*<<< orphan*/  CONS_SCRSHOT ; 
 int DUMP_ALL ; 
 int DUMP_FMT_RAW ; 
 int DUMP_FMT_REV ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
dump_screen(int mode, int opt)
{
	scrshot_t shot;
	vid_info_t info;

	info.size = sizeof(info);
	if (ioctl(0, CONS_GETINFO, &info) == -1) {
		revert();
		err(1, "getting console information");
	}

	shot.x = shot.y = 0;
	shot.xsize = info.mv_csz;
	shot.ysize = info.mv_rsz;
	if (opt == DUMP_ALL)
		shot.ysize += info.mv_hsz;

	shot.buf = alloca(shot.xsize * shot.ysize * sizeof(u_int16_t));
	if (shot.buf == NULL) {
		revert();
		errx(1, "failed to allocate memory for dump");
	}

	if (ioctl(0, CONS_SCRSHOT, &shot) == -1) {
		revert();
		err(1, "dumping screen");
	}

	if (mode == DUMP_FMT_RAW) {
		printf("SCRSHOT_%c%c%c%c", DUMP_FMT_REV, 2,
		       shot.xsize, shot.ysize);

		fflush(stdout);

		write(STDOUT_FILENO, shot.buf,
		      shot.xsize * shot.ysize * sizeof(u_int16_t));
	} else {
		char *line;
		int x, y;
		u_int16_t ch;

		line = alloca(shot.xsize + 1);

		if (line == NULL) {
			revert();
			errx(1, "failed to allocate memory for line buffer");
		}

		for (y = 0; y < shot.ysize; y++) {
			for (x = 0; x < shot.xsize; x++) {
				ch = shot.buf[x + (y * shot.xsize)];
				ch &= 0xff;

				if (isprint(ch) == 0)
					ch = ' ';

				line[x] = (char)ch;
			}

			/* Trim trailing spaces */

			do {
				line[x--] = '\0';
			} while (line[x] == ' ' && x != 0);

			puts(line);
		}

		fflush(stdout);
	}
}