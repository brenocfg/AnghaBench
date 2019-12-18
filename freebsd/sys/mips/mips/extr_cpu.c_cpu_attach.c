#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int rm_end; char* rm_descr; scalar_t__ rm_start; int /*<<< orphan*/  rm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMAN_ARRAY ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 TYPE_1__ cpu_hardirq_rman ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static int
cpu_attach(device_t dev)
{
	int error;
#ifdef notyet
	device_t clock;
#endif

	cpu_hardirq_rman.rm_start = 0;
	cpu_hardirq_rman.rm_end = 5;
	cpu_hardirq_rman.rm_type = RMAN_ARRAY;
	cpu_hardirq_rman.rm_descr = "CPU Hard Interrupts";

	error = rman_init(&cpu_hardirq_rman);
	if (error != 0) {
		device_printf(dev, "failed to initialize irq resources\n");
		return (error);
	}
	/* XXX rman_manage_all. */
	error = rman_manage_region(&cpu_hardirq_rman,
				   cpu_hardirq_rman.rm_start,
				   cpu_hardirq_rman.rm_end);
	if (error != 0) {
		device_printf(dev, "failed to manage irq resources\n");
		return (error);
	}

	if (device_get_unit(dev) != 0)
		panic("can't attach more cpus");
	device_set_desc(dev, "MIPS32 processor");

#ifdef notyet
	clock = device_add_child(dev, "clock", device_get_unit(dev));
	if (clock == NULL)
		device_printf(dev, "clock failed to attach");
#endif

	return (bus_generic_attach(dev));
}