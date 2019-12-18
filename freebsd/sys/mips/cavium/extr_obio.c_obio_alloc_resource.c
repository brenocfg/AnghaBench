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
typedef  int /*<<< orphan*/  u_int ;
struct rman {int dummy; } ;
struct resource {int dummy; } ;
struct obio_softc {struct rman oba_rman; struct rman oba_irq_rman; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MIO_UARTX_RBR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCTEON_IRQ_UART0 ; 
 int /*<<< orphan*/  OCTEON_IRQ_UART1 ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 scalar_t__ bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct obio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_uart_tag ; 
 int /*<<< orphan*/  rman_release_resource (struct resource*) ; 
 struct resource* rman_reserve_resource (struct rman*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_rid (struct resource*,int) ; 

__attribute__((used)) static struct resource *
obio_alloc_resource(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct resource *rv;
	struct rman *rm;
	bus_space_tag_t bt = 0;
	bus_space_handle_t bh = 0;
	struct obio_softc *sc = device_get_softc(bus);

	switch (type) {
	case SYS_RES_IRQ:
		switch (device_get_unit(child)) {
		case 0:
			start = end = OCTEON_IRQ_UART0;
			break;
		case 1:
			start = end = OCTEON_IRQ_UART1;
			break;
		default:
			return (NULL);
		}
		rm = &sc->oba_irq_rman;
		break;
	case SYS_RES_MEMORY:
		return (NULL);
	case SYS_RES_IOPORT:
		rm = &sc->oba_rman;
		bt = &octeon_uart_tag;
		bh = CVMX_MIO_UARTX_RBR(device_get_unit(child));
		start = bh;
		break;
	default:
		return (NULL);
	}

	rv = rman_reserve_resource(rm, start, end, count, flags, child);
	if (rv == NULL)  {
		return (NULL);
        }
	if (type == SYS_RES_IRQ) {
		return (rv);
        }
	rman_set_rid(rv, *rid);
	rman_set_bustag(rv, bt);
	rman_set_bushandle(rv, bh);
	
	if (0) {
		if (bus_activate_resource(child, type, *rid, rv)) {
			rman_release_resource(rv);
			return (NULL);
		}
	}
	return (rv);

}