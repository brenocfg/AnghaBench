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
struct xgbe_prv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RATECHANGE ; 
 int /*<<< orphan*/  SIR1_SPEED ; 
 int /*<<< orphan*/  XSIR1_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_serdes_start_ratechange(struct xgbe_prv_data *pdata)
{
	/* Assert Rx and Tx ratechange */
	XSIR1_IOWRITE_BITS(pdata, SIR1_SPEED, RATECHANGE, 1);
}