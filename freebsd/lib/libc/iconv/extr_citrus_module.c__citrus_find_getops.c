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
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ _citrus_module_t ;

/* Variables and functions */
 int PATH_MAX ; 
 void* dlsym (void*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

void *
_citrus_find_getops(_citrus_module_t handle, const char *modname,
    const char *ifname)
{
	char name[PATH_MAX];
	void *p;

	snprintf(name, sizeof(name), "_citrus_%s_%s_getops",
	    modname, ifname);
	p = dlsym((void *)handle, name);
	return (p);
}