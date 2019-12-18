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
typedef  unsigned long long uint64_t ;
struct xgbe_prv_data {unsigned long an_start; int kr_state; int kx_state; } ;
typedef  enum xgbe_rx { ____Placeholder_xgbe_rx } xgbe_rx ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 int XGBE_AN_ERROR ; 
 scalar_t__ XGBE_AN_MS_TIMEOUT ; 
#define  XGBE_RX_BPA 129 
#define  XGBE_RX_XNP 128 
 scalar_t__ hz ; 
 unsigned long ticks ; 
 int xgbe_an_rx_bpa (struct xgbe_prv_data*,int*) ; 
 int xgbe_an_rx_xnp (struct xgbe_prv_data*,int*) ; 
 scalar_t__ xgbe_in_kr_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_an xgbe_an_page_received(struct xgbe_prv_data *pdata)
{
	enum xgbe_rx *state;
	unsigned long an_timeout;
	enum xgbe_an ret;

	if (!pdata->an_start) {
		pdata->an_start = ticks;
	} else {
		an_timeout = pdata->an_start +
		    ((uint64_t)XGBE_AN_MS_TIMEOUT * (uint64_t)hz) / 1000ull;
		if ((int)(ticks - an_timeout) > 0) {
			/* Auto-negotiation timed out, reset state */
			pdata->kr_state = XGBE_RX_BPA;
			pdata->kx_state = XGBE_RX_BPA;

			pdata->an_start = ticks;
		}
	}

	state = xgbe_in_kr_mode(pdata) ? &pdata->kr_state
					   : &pdata->kx_state;

	switch (*state) {
	case XGBE_RX_BPA:
		ret = xgbe_an_rx_bpa(pdata, state);
		break;

	case XGBE_RX_XNP:
		ret = xgbe_an_rx_xnp(pdata, state);
		break;

	default:
		ret = XGBE_AN_ERROR;
	}

	return ret;
}