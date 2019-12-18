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
struct pcpu {int /*<<< orphan*/  pc_device; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int device_get_unit (int /*<<< orphan*/ ) ; 
 struct pcpu* pcpu_find (int) ; 

__attribute__((used)) static int
xenpvcpu_attach(device_t dev)
{
	struct pcpu *pc;
	int cpu;

	cpu = device_get_unit(dev);
	pc = pcpu_find(cpu);
	pc->pc_device = dev;
	return (0);
}