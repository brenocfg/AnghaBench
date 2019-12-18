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
struct vtcon_softc {int vtcon_flags; int vtcon_max_ports; } ;
struct virtio_console_config {int /*<<< orphan*/  max_nr_ports; } ;

/* Variables and functions */
 int VTCON_FLAG_MULTIPORT ; 
 int /*<<< orphan*/  VTCON_MAX_PORTS ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtcon_determine_max_ports(struct vtcon_softc *sc,
    struct virtio_console_config *concfg)
{

	if (sc->vtcon_flags & VTCON_FLAG_MULTIPORT) {
		sc->vtcon_max_ports =
		    min(concfg->max_nr_ports, VTCON_MAX_PORTS);
		if (sc->vtcon_max_ports == 0)
			sc->vtcon_max_ports = 1;
	} else
		sc->vtcon_max_ports = 1;
}