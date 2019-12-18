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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  intr_stray; int /*<<< orphan*/  intr_ok; } ;
struct arge_softc {int arge_intr_status; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_DMA_INTR ; 
 int /*<<< orphan*/  AR71XX_DMA_INTR_STATUS ; 
 int /*<<< orphan*/  ARGEDEBUG (struct arge_softc*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  ARGE_DBG_INTR ; 
 int ARGE_READ (struct arge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARGE_WRITE (struct arge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DMA_INTR_ALL ; 
 int FILTER_SCHEDULE_THREAD ; 
 int FILTER_STRAY ; 

__attribute__((used)) static int
arge_intr_filter(void *arg)
{
	struct arge_softc	*sc = arg;
	uint32_t		status, ints;

	status = ARGE_READ(sc, AR71XX_DMA_INTR_STATUS);
	ints = ARGE_READ(sc, AR71XX_DMA_INTR);

	ARGEDEBUG(sc, ARGE_DBG_INTR, "int mask(filter) = %b\n", ints,
	    "\20\10RX_BUS_ERROR\7RX_OVERFLOW\5RX_PKT_RCVD"
	    "\4TX_BUS_ERROR\2TX_UNDERRUN\1TX_PKT_SENT");
	ARGEDEBUG(sc, ARGE_DBG_INTR, "status(filter) = %b\n", status,
	    "\20\10RX_BUS_ERROR\7RX_OVERFLOW\5RX_PKT_RCVD"
	    "\4TX_BUS_ERROR\2TX_UNDERRUN\1TX_PKT_SENT");

	if (status & DMA_INTR_ALL) {
		sc->arge_intr_status |= status;
		ARGE_WRITE(sc, AR71XX_DMA_INTR, 0);
		sc->stats.intr_ok++;
		return (FILTER_SCHEDULE_THREAD);
	}

	sc->arge_intr_status = 0;
	sc->stats.intr_stray++;
	return (FILTER_STRAY);
}