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

/* Variables and functions */
 int TZ_NUMLEVELS ; 
 char const** aclevel_string ; 

__attribute__((used)) static __inline const char *
acpi_tz_aclevel_string(int active)
{
    if (active < -1 || active >= TZ_NUMLEVELS)
	return (aclevel_string[0]);

    return (aclevel_string[active + 1]);
}