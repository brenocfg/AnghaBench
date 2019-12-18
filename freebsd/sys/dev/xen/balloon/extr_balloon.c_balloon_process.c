#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ current_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  balloon_mutex ; 
 TYPE_1__ bs ; 
 scalar_t__ current_target () ; 
 scalar_t__ decrease_reservation (long) ; 
 int hz ; 
 scalar_t__ increase_reservation (long) ; 
 int /*<<< orphan*/  msleep (void (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
balloon_process(void *unused)
{
	int need_sleep = 0;
	long credit;
	
	mtx_lock(&balloon_mutex);
	for (;;) {
		int sleep_time;

		do {
			credit = current_target() - bs.current_pages;
			if (credit > 0)
				need_sleep = (increase_reservation(credit) != 0);
			if (credit < 0)
				need_sleep = (decrease_reservation(-credit) != 0);
			
		} while ((credit != 0) && !need_sleep);
		
		/* Schedule more work if there is some still to be done. */
		if (current_target() != bs.current_pages)
			sleep_time = hz;
		else
			sleep_time = 0;

		msleep(balloon_process, &balloon_mutex, 0, "balloon",
		       sleep_time);
	}
	mtx_unlock(&balloon_mutex);
}