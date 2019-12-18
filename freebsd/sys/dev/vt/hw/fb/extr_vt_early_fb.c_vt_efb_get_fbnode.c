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
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  stdout ;
typedef  int phandle_t ;
typedef  char ihandle_t ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_getprop (int,char*,char*,int) ; 
 int OF_instance_to_package (char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static phandle_t
vt_efb_get_fbnode()
{
	phandle_t chosen, node;
	ihandle_t stdout;
	char type[64];

	chosen = OF_finddevice("/chosen");
	OF_getprop(chosen, "stdout", &stdout, sizeof(stdout));
	node = OF_instance_to_package(stdout);
	if (node != -1) {
		/* The "/chosen/stdout" present. */
		OF_getprop(node, "device_type", type, sizeof(type));
		/* Check if it has "display" type. */
		if (strcmp(type, "display") == 0)
			return (node);
	}
	/* Try device with name "screen". */
	node = OF_finddevice("screen");

	return (node);
}