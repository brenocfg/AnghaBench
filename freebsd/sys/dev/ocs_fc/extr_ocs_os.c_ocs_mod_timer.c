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
typedef  int uint32_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  callout; } ;
typedef  TYPE_1__ ocs_timer_t ;
typedef  int int32_t ;

/* Variables and functions */
 int INT32_MAX ; 
 int /*<<< orphan*/  __ocs_callout ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*) ; 
 int tvtohz (struct timeval*) ; 

int32_t
ocs_mod_timer(ocs_timer_t *timer, uint32_t timeout_ms)
{
	struct	timeval tv;
	int	hz;

	if (timer == NULL) {
		ocs_log_err(NULL, "bad parameter\n");
		return -1;
	}

	tv.tv_sec  = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;

	hz = tvtohz(&tv);
	if (hz < 0)
		hz = INT32_MAX;
	if (hz == 0)
		hz = 1;

	mtx_lock(&timer->lock);
		callout_reset(&timer->callout, hz, __ocs_callout, timer);
	mtx_unlock(&timer->lock);

	return 0;
}