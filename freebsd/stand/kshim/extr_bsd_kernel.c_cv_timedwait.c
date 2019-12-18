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
struct mtx {int dummy; } ;
struct cv {int sleeping; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  callout_process (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int ticks ; 
 int /*<<< orphan*/  usb_idle () ; 

int
cv_timedwait(struct cv *cv, struct mtx *mtx, int timo)
{
	int start = ticks;
	int delta;
	int time = 0;

	if (cv->sleeping)
		return (EWOULDBLOCK);	/* not allowed */

	cv->sleeping = 1;

	while (cv->sleeping) {
		if (timo >= 0) {
			delta = ticks - start;
			if (delta >= timo || delta < 0)
				break;
		}
		mtx_unlock(mtx);

		usb_idle();

		if (++time >= (1000000 / hz)) {
			time = 0;
			callout_process(1);
		}

		/* Sleep for 1 us */
		delay(1);

		mtx_lock(mtx);
	}

	if (cv->sleeping) {
		cv->sleeping = 0;
		return (EWOULDBLOCK);	/* not allowed */
	}
	return (0);
}