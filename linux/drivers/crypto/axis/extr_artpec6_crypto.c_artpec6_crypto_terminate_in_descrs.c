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
struct TYPE_2__ {int intr; } ;
struct pdma_descr {TYPE_1__ ctrl; } ;
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_descriptors {int in_cnt; struct pdma_descr* in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MODULE_NAME ; 
 int PDMA_DESCR_COUNT ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
artpec6_crypto_terminate_in_descrs(struct artpec6_crypto_req_common *common)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;
	struct pdma_descr *d;

	if (!dma->in_cnt || dma->in_cnt > PDMA_DESCR_COUNT) {
		pr_err("%s: IN descriptor list is %s\n",
			MODULE_NAME, dma->in_cnt ? "empty" : "full");
		return -EINVAL;
	}

	d = &dma->in[dma->in_cnt-1];
	d->ctrl.intr = 1;
	return 0;
}