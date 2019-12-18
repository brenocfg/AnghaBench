#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cur; } ;
struct wpi_softc {TYPE_1__ rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_FH_RX_WPTR ; 
 int /*<<< orphan*/  WPI_WRITE (struct wpi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wpi_update_rx_ring(struct wpi_softc *sc)
{
	WPI_WRITE(sc, WPI_FH_RX_WPTR, sc->rxq.cur & ~7);
}