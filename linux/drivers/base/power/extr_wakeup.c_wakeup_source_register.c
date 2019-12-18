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
struct wakeup_source {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ device_is_registered (struct device*) ; 
 int /*<<< orphan*/  wakeup_source_add (struct wakeup_source*) ; 
 struct wakeup_source* wakeup_source_create (char const*) ; 
 int /*<<< orphan*/  wakeup_source_free (struct wakeup_source*) ; 
 int wakeup_source_sysfs_add (struct device*,struct wakeup_source*) ; 

struct wakeup_source *wakeup_source_register(struct device *dev,
					     const char *name)
{
	struct wakeup_source *ws;
	int ret;

	ws = wakeup_source_create(name);
	if (ws) {
		if (!dev || device_is_registered(dev)) {
			ret = wakeup_source_sysfs_add(dev, ws);
			if (ret) {
				wakeup_source_free(ws);
				return NULL;
			}
		}
		wakeup_source_add(ws);
	}
	return ws;
}