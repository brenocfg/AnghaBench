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
typedef  int /*<<< orphan*/  u16 ;
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  RATECHANGE ; 
 int /*<<< orphan*/  RESETB_RXD ; 
 int /*<<< orphan*/  RXTX_REG6 ; 
 int /*<<< orphan*/  RX_READY ; 
 int /*<<< orphan*/  SIR0_STATUS ; 
 int /*<<< orphan*/  SIR1_SPEED ; 
 int /*<<< orphan*/  TX_READY ; 
 unsigned int XGBE_RATECHANGE_COUNT ; 
 int /*<<< orphan*/  XRXTX_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSIR0_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSIR1_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XSIR_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_serdes_complete_ratechange(struct xgbe_prv_data *pdata)
{
	unsigned int wait;
	u16 status;

	/* Release Rx and Tx ratechange */
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, RATECHANGE, 0);

	/* Wait for Rx and Tx ready */
	wait = XGBE_RATECHANGE_COUNT;
	while (wait--) {
		DELAY(50);

		status = XSIR0_IOREAD(pdata, SIR0_STATUS);
		if (XSIR_GET_BITS(status, SIR0_STATUS, RX_READY) &&
		    XSIR_GET_BITS(status, SIR0_STATUS, TX_READY))
			goto rx_reset;
	}

rx_reset:
	/* Perform Rx reset for the DFE changes */
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG6, RESETB_RXD, 0);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG6, RESETB_RXD, 1);
}