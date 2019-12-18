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
 char* ofw_bus_get_compat (int /*<<< orphan*/ ) ; 
 char* ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

int
ofw_bus_gen_child_pnpinfo_str(device_t cbdev, device_t child, char *buf,
    size_t buflen)
{

	*buf = '\0';
	if (!ofw_bus_status_okay(child))
		return (0);

	if (ofw_bus_get_name(child) != NULL) {
		strlcat(buf, "name=", buflen);
		strlcat(buf, ofw_bus_get_name(child), buflen);
	}

	if (ofw_bus_get_compat(child) != NULL) {
		strlcat(buf, " compat=", buflen);
		strlcat(buf, ofw_bus_get_compat(child), buflen);
	}

	return (0);
}