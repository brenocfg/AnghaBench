#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {char* rm_descr; void* rm_type; int /*<<< orphan*/  rm_end; scalar_t__ rm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 void* RMAN_ARRAY ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 TYPE_1__ irq_rman ; 
 TYPE_1__ mem_rman ; 
 int /*<<< orphan*/  nexus_add_child (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 scalar_t__ rman_manage_region (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nexus_attach(device_t dev)
{

	mem_rman.rm_start = 0;
	mem_rman.rm_end = BUS_SPACE_MAXADDR;
	mem_rman.rm_type = RMAN_ARRAY;
	mem_rman.rm_descr = "I/O memory addresses";
	if (rman_init(&mem_rman) ||
	    rman_manage_region(&mem_rman, 0, BUS_SPACE_MAXADDR))
		panic("nexus_attach mem_rman");
	irq_rman.rm_start = 0;
	irq_rman.rm_end = ~0;
	irq_rman.rm_type = RMAN_ARRAY;
	irq_rman.rm_descr = "Interrupts";
	if (rman_init(&irq_rman) || rman_manage_region(&irq_rman, 0, ~0))
		panic("nexus_attach irq_rman");

	nexus_add_child(dev, 8, "timer", 0);
	nexus_add_child(dev, 9, "rcons", 0);
	nexus_add_child(dev, 10, "ofwbus", 0);

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	return (0);
}