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
struct xgbe_prv_data {scalar_t__ an_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_INT ; 
 int /*<<< orphan*/  MDIO_AN_INTMASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 scalar_t__ XGBE_AN_INT_MASK ; 
 scalar_t__ XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xgbe_an_state_machine (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_an_isr(void *data)
{
	struct xgbe_prv_data *pdata = (struct xgbe_prv_data *)data;

	/* Disable AN interrupts */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);

	/* Save the interrupt(s) that fired */
	pdata->an_int = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_INT);

	if (pdata->an_int) {
		/* Clear the interrupt(s) that fired and process them */
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, ~pdata->an_int);

		xgbe_an_state_machine(pdata);
	} else {
		/* Enable AN interrupts */
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK,
			    XGBE_AN_INT_MASK);
	}
}