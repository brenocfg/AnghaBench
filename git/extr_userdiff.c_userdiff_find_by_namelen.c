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
struct userdiff_driver {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct userdiff_driver*) ; 
 struct userdiff_driver* builtin_drivers ; 
 struct userdiff_driver* drivers ; 
 int ndrivers ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static struct userdiff_driver *userdiff_find_by_namelen(const char *k, int len)
{
	int i;
	for (i = 0; i < ndrivers; i++) {
		struct userdiff_driver *drv = drivers + i;
		if (!strncmp(drv->name, k, len) && !drv->name[len])
			return drv;
	}
	for (i = 0; i < ARRAY_SIZE(builtin_drivers); i++) {
		struct userdiff_driver *drv = builtin_drivers + i;
		if (!strncmp(drv->name, k, len) && !drv->name[len])
			return drv;
	}
	return NULL;
}