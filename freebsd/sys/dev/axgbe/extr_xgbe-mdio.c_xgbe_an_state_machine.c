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
struct xgbe_prv_data {int an_state; int an_int; int an_result; int parallel_detect; int /*<<< orphan*/  an_mutex; scalar_t__ an_start; void* kx_state; void* kr_state; int /*<<< orphan*/  an_supported; } ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_INT ; 
 int /*<<< orphan*/  MDIO_AN_INTMASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
#define  XGBE_AN_COMPLETE 132 
 void* XGBE_AN_ERROR ; 
#define  XGBE_AN_INCOMPAT_LINK 131 
 int XGBE_AN_INC_LINK ; 
 int XGBE_AN_INT_CMPLT ; 
 int /*<<< orphan*/  XGBE_AN_INT_MASK ; 
#define  XGBE_AN_NO_LINK 130 
#define  XGBE_AN_PAGE_RECEIVED 129 
 int XGBE_AN_PG_RCV ; 
#define  XGBE_AN_READY 128 
 void* XGBE_RX_BPA ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int xgbe_an_incompat_link (struct xgbe_prv_data*) ; 
 int xgbe_an_page_received (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_an_state_machine(struct xgbe_prv_data *pdata)
{
	enum xgbe_an cur_state = pdata->an_state;

	sx_xlock(&pdata->an_mutex);

	if (!pdata->an_int)
		goto out;

next_int:
	if (pdata->an_int & XGBE_AN_PG_RCV) {
		pdata->an_state = XGBE_AN_PAGE_RECEIVED;
		pdata->an_int &= ~XGBE_AN_PG_RCV;
	} else if (pdata->an_int & XGBE_AN_INC_LINK) {
		pdata->an_state = XGBE_AN_INCOMPAT_LINK;
		pdata->an_int &= ~XGBE_AN_INC_LINK;
	} else if (pdata->an_int & XGBE_AN_INT_CMPLT) {
		pdata->an_state = XGBE_AN_COMPLETE;
		pdata->an_int &= ~XGBE_AN_INT_CMPLT;
	} else {
		pdata->an_state = XGBE_AN_ERROR;
	}

	pdata->an_result = pdata->an_state;

again:
	cur_state = pdata->an_state;

	switch (pdata->an_state) {
	case XGBE_AN_READY:
		pdata->an_supported = 0;
		break;

	case XGBE_AN_PAGE_RECEIVED:
		pdata->an_state = xgbe_an_page_received(pdata);
		pdata->an_supported++;
		break;

	case XGBE_AN_INCOMPAT_LINK:
		pdata->an_supported = 0;
		pdata->parallel_detect = 0;
		pdata->an_state = xgbe_an_incompat_link(pdata);
		break;

	case XGBE_AN_COMPLETE:
		pdata->parallel_detect = pdata->an_supported ? 0 : 1;
		break;

	case XGBE_AN_NO_LINK:
		break;

	default:
		pdata->an_state = XGBE_AN_ERROR;
	}

	if (pdata->an_state == XGBE_AN_NO_LINK) {
		pdata->an_int = 0;
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, 0);
	} else if (pdata->an_state == XGBE_AN_ERROR) {
		pdata->an_int = 0;
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, 0);
	}

	if (pdata->an_state >= XGBE_AN_COMPLETE) {
		pdata->an_result = pdata->an_state;
		pdata->an_state = XGBE_AN_READY;
		pdata->kr_state = XGBE_RX_BPA;
		pdata->kx_state = XGBE_RX_BPA;
		pdata->an_start = 0;
	}

	if (cur_state != pdata->an_state)
		goto again;

	if (pdata->an_int)
		goto next_int;

out:
	/* Enable AN interrupts on the way out */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, XGBE_AN_INT_MASK);

	sx_xunlock(&pdata->an_mutex);
}