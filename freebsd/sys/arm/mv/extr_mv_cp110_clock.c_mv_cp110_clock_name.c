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
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ asprintf (char**,int /*<<< orphan*/ ,char*,char const*,int) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,char const*) ; 

__attribute__((used)) static char *
mv_cp110_clock_name(device_t dev, const char *name)
{
	char *clkname = NULL;
	int unit;

	unit = device_get_unit(dev);
	if (asprintf(&clkname, M_DEVBUF, "%s-%d", name, unit) <= 0)
		panic("Cannot generate unique clock name for %s\n", name);
	return (clkname);
}