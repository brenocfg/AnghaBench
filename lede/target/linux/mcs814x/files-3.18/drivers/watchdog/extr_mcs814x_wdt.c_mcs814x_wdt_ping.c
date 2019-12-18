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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcs814x_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcs814x_wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  mcs814x_wdt_stop (struct watchdog_device*) ; 

__attribute__((used)) static int mcs814x_wdt_ping(struct watchdog_device *dev)
{
	/* restart the watchdog */
	mcs814x_wdt_stop(dev);
	mcs814x_wdt_set_timeout(dev, dev->timeout);
	mcs814x_wdt_start(dev);

	return 0;
}