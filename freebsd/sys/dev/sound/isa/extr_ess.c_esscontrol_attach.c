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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 int port_rd (struct resource*,int) ; 
 int /*<<< orphan*/  port_wr (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
esscontrol_attach(device_t dev)
{
#ifdef notyet
    	struct resource *io;
	int rid, i, x;

	rid = 0;
    	io = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid, RF_ACTIVE);
	x = 0;
	for (i = 0; i < 0x100; i++) {
		port_wr(io, 0, i);
		x = port_rd(io, 1);
		if ((i & 0x0f) == 0)
			printf("%3.3x: ", i);
		printf("%2.2x ", x);
		if ((i & 0x0f) == 0x0f)
			printf("\n");
	}
	bus_release_resource(dev, SYS_RES_IOPORT, 0, io);
	io = NULL;
#endif

    	return 0;
}