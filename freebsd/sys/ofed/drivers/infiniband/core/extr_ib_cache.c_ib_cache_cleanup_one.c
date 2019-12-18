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
struct TYPE_2__ {int /*<<< orphan*/  event_handler; } ;
struct ib_device {TYPE_1__ cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_table_cleanup_one (struct ib_device*) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_wq ; 

void ib_cache_cleanup_one(struct ib_device *device)
{
	/* The cleanup function unregisters the event handler,
	 * waits for all in-progress workqueue elements and cleans
	 * up the GID cache. This function should be called after
	 * the device was removed from the devices list and all
	 * clients were removed, so the cache exists but is
	 * non-functional and shouldn't be updated anymore.
	 */
	ib_unregister_event_handler(&device->cache.event_handler);
	flush_workqueue(ib_wq);
	gid_table_cleanup_one(device);
}