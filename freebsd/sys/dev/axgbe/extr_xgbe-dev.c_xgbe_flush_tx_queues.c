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
struct TYPE_2__ {int /*<<< orphan*/  version; } ;
struct xgbe_prv_data {unsigned int tx_q_count; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  FTQ ; 
 int /*<<< orphan*/  MAC_VR ; 
 int /*<<< orphan*/  MTL_Q_TQOMR ; 
 int /*<<< orphan*/  SNPSVER ; 
 int XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XGMAC_MTL_IOREAD_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_MTL_IOWRITE_BITS (struct xgbe_prv_data*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xgbe_flush_tx_queues(struct xgbe_prv_data *pdata)
{
	unsigned int i, count;

	if (XGMAC_GET_BITS(pdata->hw_feat.version, MAC_VR, SNPSVER) < 0x21)
		return 0;

	for (i = 0; i < pdata->tx_q_count; i++)
		XGMAC_MTL_IOWRITE_BITS(pdata, i, MTL_Q_TQOMR, FTQ, 1);

	/* Poll Until Poll Condition */
	for (i = 0; i < pdata->tx_q_count; i++) {
		count = 2000;
		while (--count && XGMAC_MTL_IOREAD_BITS(pdata, i,
							MTL_Q_TQOMR, FTQ))
			DELAY(500);

		if (!count)
			return -EBUSY;
	}

	return 0;
}