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
struct TYPE_2__ {int /*<<< orphan*/  (* set_gmii_speed ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/ * serdes_dfe_tap_ena; int /*<<< orphan*/ * serdes_dfe_tap_cfg; int /*<<< orphan*/ * serdes_pq_skew; int /*<<< orphan*/ * serdes_blwc; int /*<<< orphan*/ * serdes_tx_amp; int /*<<< orphan*/ * serdes_cdr_rate; TYPE_1__ hw_if; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLWC_ENA ; 
 int /*<<< orphan*/  CDR_RATE ; 
 int /*<<< orphan*/  DATARATE ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 unsigned int MDIO_CTRL1_SPEED1G ; 
 unsigned int MDIO_CTRL1_SPEEDSEL ; 
 int /*<<< orphan*/  MDIO_CTRL2 ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 unsigned int MDIO_PCS_CTRL2_10GBX ; 
 unsigned int MDIO_PCS_CTRL2_TYPE ; 
 int /*<<< orphan*/  PLLSEL ; 
 int /*<<< orphan*/  PQ_REG ; 
 int /*<<< orphan*/  RXDFE_CONFIG ; 
 int /*<<< orphan*/  RXTX_REG114 ; 
 int /*<<< orphan*/  RXTX_REG129 ; 
 int /*<<< orphan*/  RXTX_REG20 ; 
 int /*<<< orphan*/  RXTX_REG22 ; 
 int /*<<< orphan*/  SIR1_SPEED ; 
 int /*<<< orphan*/  TXAMP ; 
 int /*<<< orphan*/  WORDMODE ; 
 size_t XGBE_SPEED_1000 ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_PLL ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_RATE ; 
 int /*<<< orphan*/  XGBE_SPEED_1000_WORD ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XRXTX_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XRXTX_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSIR1_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_disable_kr_training (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_pcs_power_cycle (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_serdes_complete_ratechange (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_serdes_start_ratechange (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_gmii_mode(struct xgbe_prv_data *pdata)
{
	unsigned int reg;

	/* Disable KR training */
	xgbe_an_disable_kr_training(pdata);

	/* Set MAC to 1G speed */
	pdata->hw_if.set_gmii_speed(pdata);

	/* Set PCS to KX/1G speed */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL2);
	reg &= ~MDIO_PCS_CTRL2_TYPE;
	reg |= MDIO_PCS_CTRL2_10GBX;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL2, reg);

	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_CTRL1);
	reg &= ~MDIO_CTRL1_SPEEDSEL;
	reg |= MDIO_CTRL1_SPEED1G;
	XMDIO_WRITE(pdata, MDIO_MMD_PCS, MDIO_CTRL1, reg);

	xgbe_pcs_power_cycle(pdata);

	/* Set SerDes to 1G speed */
	xgbe_serdes_start_ratechange(pdata);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, DATARATE, XGBE_SPEED_1000_RATE);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, WORDMODE, XGBE_SPEED_1000_WORD);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, PLLSEL, XGBE_SPEED_1000_PLL);

	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, CDR_RATE,
			   pdata->serdes_cdr_rate[XGBE_SPEED_1000]);
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, TXAMP,
			   pdata->serdes_tx_amp[XGBE_SPEED_1000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG20, BLWC_ENA,
			   pdata->serdes_blwc[XGBE_SPEED_1000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG114, PQ_REG,
			   pdata->serdes_pq_skew[XGBE_SPEED_1000]);
	XRXTX_IOWRITE_BITS(pdata, RXTX_REG129, RXDFE_CONFIG,
			   pdata->serdes_dfe_tap_cfg[XGBE_SPEED_1000]);
	XRXTX_IOWRITE(pdata, RXTX_REG22,
		      pdata->serdes_dfe_tap_ena[XGBE_SPEED_1000]);

	xgbe_serdes_complete_ratechange(pdata);
}