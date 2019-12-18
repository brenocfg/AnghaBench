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
typedef  int /*<<< orphan*/  reg ;
typedef  int phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int OF_child (int) ; 
 int OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (int,char*,int*,int) ; 
 int OF_peer (int) ; 

__attribute__((used)) static phandle_t
qman_portal_find_cpu(int cpu)
{
	phandle_t node;
	pcell_t reg;

	node = OF_finddevice("/cpus");
	if (node == -1)
		return (-1);

	for (node = OF_child(node); node != 0; node = OF_peer(node)) {
		if (OF_getprop(node, "reg", &reg, sizeof(reg)) <= 0)
			continue;
		if (reg == cpu)
			return (node);
	}
	return (-1);
}