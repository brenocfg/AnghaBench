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
struct mly_softc {int /*<<< orphan*/ * mly_packet; int /*<<< orphan*/  mly_packetmap; int /*<<< orphan*/  mly_packet_dmat; int /*<<< orphan*/  mly_buffer_dmat; } ;
struct mly_command {int /*<<< orphan*/  mc_datamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mly_alloc_command (struct mly_softc*,struct mly_command**) ; 

__attribute__((used)) static void
mly_release_commands(struct mly_softc *sc)
{
    struct mly_command	*mc;

    /* throw away command buffer DMA maps */
    while (mly_alloc_command(sc, &mc) == 0)
	bus_dmamap_destroy(sc->mly_buffer_dmat, mc->mc_datamap);

    /* release the packet storage */
    if (sc->mly_packet != NULL) {
	bus_dmamap_unload(sc->mly_packet_dmat, sc->mly_packetmap);
	bus_dmamem_free(sc->mly_packet_dmat, sc->mly_packet, sc->mly_packetmap);
	sc->mly_packet = NULL;
    }
}