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
typedef  int u_int ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int isa_get_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int isa_get_port (int /*<<< orphan*/ ) ; 
 int nitems (int*) ; 
 int* rc_ports ; 

__attribute__((used)) static int
rc_probe(device_t dev)
{
	u_int port;
	int i, found;

	/*
	 * We don't know of any PnP ID's for these cards.
	 */
	if (isa_get_logicalid(dev) != 0)
		return (ENXIO);

	/*
	 * We have to have an IO port hint that is valid.
	 */
	port = isa_get_port(dev);
	if (port == -1)
		return (ENXIO);
	found = 0;
	for (i = 0; i < nitems(rc_ports); i++)
		if (rc_ports[i] == port) {
			found = 1;
			break;
		}
	if (!found)
		return (ENXIO);

	/*
	 * We have to have an IRQ hint.
	 */
	if (isa_get_irq(dev) == -1)
		return (ENXIO);

	device_set_desc(dev, "SDL Riscom/8");
	return (0);
}