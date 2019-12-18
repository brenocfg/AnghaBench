#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  decode_buf; int /*<<< orphan*/  dma_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  decode_buf; int /*<<< orphan*/  dma_buf; } ;
struct sfxge_port {scalar_t__ init_state; int /*<<< orphan*/ * sc; TYPE_2__ mac_stats; TYPE_1__ phy_stats; int /*<<< orphan*/  link_mode; } ;
struct sfxge_softc {struct sfxge_port port; } ;
typedef  int /*<<< orphan*/  efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_LINK_UNKNOWN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_SFXGE ; 
 scalar_t__ SFXGE_PORT_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_PORT_LOCK_DESTROY (struct sfxge_port*) ; 
 scalar_t__ SFXGE_PORT_UNINITIALIZED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 

void
sfxge_port_fini(struct sfxge_softc *sc)
{
	struct sfxge_port *port;
	efsys_mem_t *esmp;

	port = &sc->port;
	esmp = &port->mac_stats.dma_buf;

	KASSERT(port->init_state == SFXGE_PORT_INITIALIZED,
	    ("Port not initialized"));

	port->init_state = SFXGE_PORT_UNINITIALIZED;

	port->link_mode = EFX_LINK_UNKNOWN;

	/* Finish with PHY DMA memory */
	sfxge_dma_free(&port->phy_stats.dma_buf);
	free(port->phy_stats.decode_buf, M_SFXGE);

	sfxge_dma_free(esmp);
	free(port->mac_stats.decode_buf, M_SFXGE);

	SFXGE_PORT_LOCK_DESTROY(port);

	port->sc = NULL;
}