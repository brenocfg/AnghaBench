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
typedef  int uint32_t ;
struct ntb_plx_softc {int port; int /*<<< orphan*/  conf_res; scalar_t__ link; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PLX_PORT_CONTROL (struct ntb_plx_softc*) ; 
 int bus_read_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int,int) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_plx_link_disable(device_t dev)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	uint32_t reg, val;

	/* Link disable for Link Interface would be suicidal. */
	if (sc->link)
		return (0);

	reg = PLX_PORT_CONTROL(sc);
	val = bus_read_4(sc->conf_res, reg);
	val |= (1 << (sc->port & 7));
	bus_write_4(sc->conf_res, reg, val);
	return (0);
}