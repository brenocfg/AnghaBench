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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XST_NIL ; 
 char* xenbus_get_node (int /*<<< orphan*/ ) ; 
 int xs_gather (int /*<<< orphan*/ ,char const*,char*,char*,int*,int /*<<< orphan*/ *) ; 

int
xenbus_dev_is_online(device_t dev)
{
	const char *path;
	int error;
	int value;

	path = xenbus_get_node(dev);
	error = xs_gather(XST_NIL, path, "online", "%d", &value, NULL);
	if (error != 0) {
		/* Default to not online. */
		value = 0;
	}

	return (value);
}