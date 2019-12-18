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
typedef  int /*<<< orphan*/  xs_watch_cb_t ;
struct xs_watch {char* node; uintptr_t callback_data; int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*,char*) ; 
 int xs_register_watch (struct xs_watch*) ; 

int 
xenbus_watch_path(device_t dev, char *path, struct xs_watch *watch, 
    xs_watch_cb_t *callback, uintptr_t callback_data)
{
	int error;

	watch->node = path;
	watch->callback = callback;
	watch->callback_data = callback_data;

	error = xs_register_watch(watch);

	if (error) {
		watch->node = NULL;
		watch->callback = NULL;
		xenbus_dev_fatal(dev, error, "adding watch on %s", path);
	}

	return (error);
}