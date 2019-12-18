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
struct vt_device {int dummy; } ;
typedef  int /*<<< orphan*/  stdout ;
typedef  int phandle_t ;
typedef  char ihandle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CN_DEAD ; 
 int CN_INTERNAL ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int OF_instance_to_package (char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
ofwfb_probe(struct vt_device *vd)
{
	phandle_t chosen, node;
	ihandle_t stdout;
	char buf[64];

	chosen = OF_finddevice("/chosen");
	if (chosen == -1)
		return (CN_DEAD);

	node = -1;
	if (OF_getprop(chosen, "stdout", &stdout, sizeof(stdout)) ==
	    sizeof(stdout))
		node = OF_instance_to_package(stdout);
	if (node == -1)
		if (OF_getprop(chosen, "stdout-path", buf, sizeof(buf)) > 0)
			node = OF_finddevice(buf);
	if (node == -1) {
		/*
		 * The "/chosen/stdout" does not exist try
		 * using "screen" directly.
		 */
		node = OF_finddevice("screen");
	}
	OF_getprop(node, "device_type", buf, sizeof(buf));
	if (strcmp(buf, "display") != 0)
		return (CN_DEAD);

	/* Looks OK... */
	return (CN_INTERNAL);
}