#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  va_mem_size; int /*<<< orphan*/  va_mem_base; int /*<<< orphan*/  va_io_size; int /*<<< orphan*/  va_io_base; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VGA_ID ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_vendorid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_logicalid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_maddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_msize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_portsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_vendorid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vga_probe_unit (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isavga_probe(device_t dev)
{
	video_adapter_t adp;
	int error;

	/* No pnp support */
	if (isa_get_vendorid(dev))
		return (ENXIO);

	error = vga_probe_unit(device_get_unit(dev), &adp, device_get_flags(dev));
	if (error == 0) {
		device_set_desc(dev, "Generic ISA VGA");
		bus_set_resource(dev, SYS_RES_IOPORT, 0,
				 adp.va_io_base, adp.va_io_size);
		bus_set_resource(dev, SYS_RES_MEMORY, 0,
				 adp.va_mem_base, adp.va_mem_size);
		isa_set_vendorid(dev, VGA_ID);
		isa_set_logicalid(dev, VGA_ID);
#if 0
		isa_set_port(dev, adp.va_io_base);
		isa_set_portsize(dev, adp.va_io_size);
		isa_set_maddr(dev, adp.va_mem_base);
		isa_set_msize(dev, adp.va_mem_size);
#endif
	}
	return (error);
}