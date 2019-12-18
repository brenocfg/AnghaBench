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
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENXIO ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int,char const*,char*,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
phandle_chosen_propdev(phandle_t chosen, const char *name, phandle_t *node)
{
	char buf[64];
	char *sep;

	if (OF_getprop(chosen, name, buf, sizeof(buf)) <= 0)
		return (ENXIO);
	/*
	 * stdout-path may have a ':' to separate the device from the
	 * connection settings. Split the string so we just pass the former
	 * to OF_finddevice.
	 */
	sep = strchr(buf, ':');
	if (sep != NULL)
		*sep = '\0';
	if ((*node = OF_finddevice(buf)) == -1)
		return (ENXIO);

	return (0);
}