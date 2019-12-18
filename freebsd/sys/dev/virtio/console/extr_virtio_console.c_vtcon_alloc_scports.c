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
struct vtcon_softc_port {struct vtcon_softc* vcsp_sc; } ;
struct vtcon_softc {int vtcon_max_ports; struct vtcon_softc_port* vtcon_ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct vtcon_softc_port* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vtcon_alloc_scports(struct vtcon_softc *sc)
{
	struct vtcon_softc_port *scport;
	int max, i;

	max = sc->vtcon_max_ports;

	sc->vtcon_ports = malloc(sizeof(struct vtcon_softc_port) * max,
	    M_DEVBUF, M_NOWAIT | M_ZERO);
	if (sc->vtcon_ports == NULL)
		return (ENOMEM);

	for (i = 0; i < max; i++) {
		scport = &sc->vtcon_ports[i];
		scport->vcsp_sc = sc;
	}

	return (0);
}