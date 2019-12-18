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
typedef  enum poll_cmd { ____Placeholder_poll_cmd } poll_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  ifp; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int POLL_AND_CHECK_STATUS ; 
 int POLL_ONLY ; 
 int /*<<< orphan*/  microuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ netisr_poll_scheduled ; 
 int phase ; 
 int poll_burst ; 
 int poll_each_burst ; 
 int poll_handlers ; 
 int /*<<< orphan*/  poll_mtx ; 
 int /*<<< orphan*/  poll_start_t ; 
 TYPE_1__* pr ; 
 scalar_t__ reg_frac ; 
 scalar_t__ reg_frac_count ; 
 int residual_burst ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 

void
netisr_poll(void)
{
	int i, cycles;
	enum poll_cmd arg = POLL_ONLY;

	if (poll_handlers == 0)
		return;

	mtx_lock(&poll_mtx);
	if (!netisr_poll_scheduled) {
		mtx_unlock(&poll_mtx);
		return;
	}
	netisr_poll_scheduled = 0;
	phase = 3;
	if (residual_burst == 0) { /* first call in this tick */
		microuptime(&poll_start_t);
		if (++reg_frac_count == reg_frac) {
			arg = POLL_AND_CHECK_STATUS;
			reg_frac_count = 0;
		}

		residual_burst = poll_burst;
	}
	cycles = (residual_burst < poll_each_burst) ?
		residual_burst : poll_each_burst;
	residual_burst -= cycles;

	for (i = 0 ; i < poll_handlers ; i++)
		pr[i].handler(pr[i].ifp, arg, cycles);

	phase = 4;
	mtx_unlock(&poll_mtx);
}