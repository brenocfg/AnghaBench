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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TX_DESCS_SIZE ; 
 int /*<<< orphan*/  TX_SKBS_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txl_descs ; 
 int /*<<< orphan*/  txl_descs_dma ; 
 int /*<<< orphan*/  txl_skbuff ; 

__attribute__((used)) static int adm5120_switch_tx_ring_alloc(void)
{
	int err;

	txl_descs = dma_alloc_coherent(NULL, TX_DESCS_SIZE, &txl_descs_dma,
					GFP_ATOMIC);
	if (!txl_descs) {
		err = -ENOMEM;
		goto err;
	}

	txl_skbuff = kzalloc(TX_SKBS_SIZE, GFP_KERNEL);
	if (!txl_skbuff) {
		err = -ENOMEM;
		goto err;
	}

	return 0;

err:
	return err;
}