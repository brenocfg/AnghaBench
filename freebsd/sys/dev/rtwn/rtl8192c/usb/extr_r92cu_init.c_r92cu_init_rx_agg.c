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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_RXDMA_AGG_PG_TH ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL ; 
 int /*<<< orphan*/  R92C_TRXDMA_CTRL_RXDMA_AGG_EN ; 
 int /*<<< orphan*/  R92C_USB_AGG_TH ; 
 int /*<<< orphan*/  R92C_USB_AGG_TO ; 
 int /*<<< orphan*/  R92C_USB_DMA_AGG_TO ; 
 int /*<<< orphan*/  R92C_USB_SPECIAL_OPTION ; 
 int /*<<< orphan*/  R92C_USB_SPECIAL_OPTION_AGG_EN ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r92cu_init_rx_agg(struct rtwn_softc *sc)
{

	/* Rx aggregation (DMA & USB). */
	rtwn_setbits_1(sc, R92C_TRXDMA_CTRL, 0,
	    R92C_TRXDMA_CTRL_RXDMA_AGG_EN);
	rtwn_setbits_1(sc, R92C_USB_SPECIAL_OPTION, 0,
	    R92C_USB_SPECIAL_OPTION_AGG_EN);

	/* XXX dehardcode */
	rtwn_write_1(sc, R92C_RXDMA_AGG_PG_TH, 48);
	rtwn_write_1(sc, R92C_USB_DMA_AGG_TO, 4);
	rtwn_write_1(sc, R92C_USB_AGG_TH, 8);
	rtwn_write_1(sc, R92C_USB_AGG_TO, 6);
}