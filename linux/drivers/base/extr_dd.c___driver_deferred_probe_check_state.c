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
struct device {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  deferred_probe_timeout ; 
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 int /*<<< orphan*/  initcalls_done ; 

__attribute__((used)) static int __driver_deferred_probe_check_state(struct device *dev)
{
	if (!initcalls_done)
		return -EPROBE_DEFER;

	if (!deferred_probe_timeout) {
		dev_WARN(dev, "deferred probe timeout, ignoring dependency");
		return -ETIMEDOUT;
	}

	return 0;
}