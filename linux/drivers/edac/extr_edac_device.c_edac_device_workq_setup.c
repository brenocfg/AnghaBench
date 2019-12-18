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
struct edac_device_ctl_info {unsigned int poll_msec; int /*<<< orphan*/  delay; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_device_workq_function ; 
 int /*<<< orphan*/  edac_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edac_device_workq_setup(struct edac_device_ctl_info *edac_dev,
				    unsigned msec)
{
	edac_dbg(0, "\n");

	/* take the arg 'msec' and set it into the control structure
	 * to used in the time period calculation
	 * then calc the number of jiffies that represents
	 */
	edac_dev->poll_msec = msec;
	edac_dev->delay = msecs_to_jiffies(msec);

	INIT_DELAYED_WORK(&edac_dev->work, edac_device_workq_function);

	/* optimize here for the 1 second case, which will be normal value, to
	 * fire ON the 1 second time event. This helps reduce all sorts of
	 * timers firing on sub-second basis, while they are happy
	 * to fire together on the 1 second exactly
	 */
	if (edac_dev->poll_msec == 1000)
		edac_queue_work(&edac_dev->work, round_jiffies_relative(edac_dev->delay));
	else
		edac_queue_work(&edac_dev->work, edac_dev->delay);
}