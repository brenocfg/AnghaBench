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
 int /*<<< orphan*/  R92C_TXDMA_OFFSET_CHK ; 
 int /*<<< orphan*/  R92C_TXDMA_OFFSET_DROP_DATA_EN ; 
 int /*<<< orphan*/  rtwn_setbits_1_shift (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtwn_usb_drop_incorrect_tx(struct rtwn_softc *sc)
{

	rtwn_setbits_1_shift(sc, R92C_TXDMA_OFFSET_CHK, 0,
	    R92C_TXDMA_OFFSET_DROP_DATA_EN, 1);
}