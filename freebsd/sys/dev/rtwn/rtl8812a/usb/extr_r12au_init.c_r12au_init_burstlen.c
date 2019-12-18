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
typedef  int uint8_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_BURST_CNT ; 
 int /*<<< orphan*/  R12A_BURST_SZ ; 
 int R12A_BURST_SZ_M ; 
 int R12A_BURST_SZ_USB3 ; 
 int const R12A_DMA_MODE ; 
 int R12A_RXDMA_PRO ; 
 scalar_t__ R92C_TYPE_ID ; 
 int const SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r12au_init_burstlen_usb2 (struct rtwn_softc*) ; 
 int rtwn_read_1 (struct rtwn_softc*,scalar_t__) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int,int,int const) ; 

void
r12au_init_burstlen(struct rtwn_softc *sc)
{
	const uint8_t dma_count = R12A_DMA_MODE | SM(R12A_BURST_CNT, 3);

	if (rtwn_read_1(sc, R92C_TYPE_ID + 3) & 0x80)
		r12au_init_burstlen_usb2(sc);
	else {		/* USB 3.0 */
		/* Set burst packet length to 1 KB. */
		rtwn_setbits_1(sc, R12A_RXDMA_PRO, R12A_BURST_SZ_M,
		    dma_count | SM(R12A_BURST_SZ, R12A_BURST_SZ_USB3));

		rtwn_setbits_1(sc, 0xf008, 0x18, 0);
	}
}