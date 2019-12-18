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
struct cm4000_dev {int /*<<< orphan*/  flags; scalar_t__ monitor_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*) ; 
 int /*<<< orphan*/  IS_ATR_PRESENT ; 
 int /*<<< orphan*/  IS_ATR_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate_monitor (struct cm4000_dev*) ; 

__attribute__((used)) static void stop_monitor(struct cm4000_dev *dev)
{
	DEBUGP(3, dev, "-> stop_monitor\n");
	if (dev->monitor_running) {
		DEBUGP(5, dev, "stopping monitor\n");
		terminate_monitor(dev);
		/* reset monitor SM */
		clear_bit(IS_ATR_VALID, &dev->flags);
		clear_bit(IS_ATR_PRESENT, &dev->flags);
	} else
		DEBUGP(5, dev, "monitor already stopped\n");
	DEBUGP(3, dev, "<- stop_monitor\n");
}