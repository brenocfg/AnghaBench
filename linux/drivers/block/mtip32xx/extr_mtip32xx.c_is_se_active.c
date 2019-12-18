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
struct driver_data {TYPE_1__* port; int /*<<< orphan*/  dd_flag; } ;
struct TYPE_2__ {long ic_pause_timer; int /*<<< orphan*/  svc_wait; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_DDF_SEC_LOCK_BIT ; 
 int /*<<< orphan*/  MTIP_PF_SE_ACTIVE_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool is_se_active(struct driver_data *dd)
{
	if (unlikely(test_bit(MTIP_PF_SE_ACTIVE_BIT, &dd->port->flags))) {
		if (dd->port->ic_pause_timer) {
			unsigned long to = dd->port->ic_pause_timer +
							msecs_to_jiffies(1000);
			if (time_after(jiffies, to)) {
				clear_bit(MTIP_PF_SE_ACTIVE_BIT,
							&dd->port->flags);
				clear_bit(MTIP_DDF_SEC_LOCK_BIT, &dd->dd_flag);
				dd->port->ic_pause_timer = 0;
				wake_up_interruptible(&dd->port->svc_wait);
				return false;
			}
		}
		return true;
	}
	return false;
}