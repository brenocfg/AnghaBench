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
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

int
ofw_bus_is_compatible_strict(device_t dev, const char *compatible)
{
	const char *compat;
	size_t len;

	if ((compat = ofw_bus_get_compat(dev)) == NULL)
		return (0);

	len = strlen(compatible);
	if (strlen(compat) == len &&
	    strncasecmp(compat, compatible, len) == 0)
		return (1);

	return (0);
}