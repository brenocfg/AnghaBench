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
struct TYPE_4__ {int track; int dirty; TYPE_1__* dtype; } ;
struct TYPE_3__ {int (* read_fkt ) (int) ;} ;

/* Variables and functions */
 int MAX_ERRORS ; 
 int /*<<< orphan*/  del_timer (int) ; 
 int /*<<< orphan*/  fd_motor_on (int) ; 
 int /*<<< orphan*/  fd_seek (int,int) ; 
 int flush_track_timer ; 
 int /*<<< orphan*/  get_fdc (int) ; 
 int /*<<< orphan*/  non_int_flush_track (int) ; 
 int /*<<< orphan*/  raw_read (int) ; 
 int /*<<< orphan*/  rel_fdc () ; 
 int stub1 (int) ; 
 TYPE_2__* unit ; 

__attribute__((used)) static int get_track(int drive, int track)
{
	int error, errcnt;

	drive&=3;
	if (unit[drive].track == track)
		return 0;
	get_fdc(drive);
	if (!fd_motor_on(drive)) {
		rel_fdc();
		return -1;
	}

	if (unit[drive].dirty == 1) {
		del_timer (flush_track_timer + drive);
		non_int_flush_track (drive);
	}
	errcnt = 0;
	while (errcnt < MAX_ERRORS) {
		if (!fd_seek(drive, track))
			return -1;
		raw_read(drive);
		error = (*unit[drive].dtype->read_fkt)(drive);
		if (error == 0) {
			rel_fdc();
			return 0;
		}
		/* Read Error Handling: recalibrate and try again */
		unit[drive].track = -1;
		errcnt++;
	}
	rel_fdc();
	return -1;
}