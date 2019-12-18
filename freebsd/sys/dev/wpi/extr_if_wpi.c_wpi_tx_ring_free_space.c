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
typedef  size_t uint16_t ;
struct wpi_tx_ring {int queued; } ;
struct wpi_softc {struct wpi_tx_ring* txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_TXQ_STATE_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TXQ_STATE_UNLOCK (struct wpi_softc*) ; 
 int WPI_TX_RING_HIMARK ; 

__attribute__((used)) static __inline int
wpi_tx_ring_free_space(struct wpi_softc *sc, uint16_t ac)
{
	struct wpi_tx_ring *ring = &sc->txq[ac];
	int retval;

	WPI_TXQ_STATE_LOCK(sc);
	retval = WPI_TX_RING_HIMARK - ring->queued;
	WPI_TXQ_STATE_UNLOCK(sc);

	return retval;
}