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
struct wpi_tx_ring {int qid; int cur; } ;
struct wpi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_HBUS_TARG_WRPTR ; 
 int /*<<< orphan*/  WPI_WRITE (struct wpi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wpi_update_tx_ring(struct wpi_softc *sc, struct wpi_tx_ring *ring)
{
	WPI_WRITE(sc, WPI_HBUS_TARG_WRPTR, ring->qid << 8 | ring->cur);
}