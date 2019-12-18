#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int len; int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int intr; } ;
struct pdma_descr {TYPE_2__ data; TYPE_1__ ctrl; } ;
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_descriptors {scalar_t__ in_cnt; struct pdma_descr* in; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ PDMA_DESCR_COUNT ; 
 scalar_t__ fault_inject_dma_descr () ; 
 int /*<<< orphan*/  memset (struct pdma_descr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
artpec6_crypto_setup_in_descr_phys(struct artpec6_crypto_req_common *common,
			       dma_addr_t addr, unsigned int len, bool intr)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;
	struct pdma_descr *d;

	if (dma->in_cnt >= PDMA_DESCR_COUNT ||
	    fault_inject_dma_descr()) {
		pr_err("No free IN DMA descriptors available!\n");
		return -ENOSPC;
	}
	d = &dma->in[dma->in_cnt++];
	memset(d, 0, sizeof(*d));

	d->ctrl.intr = intr;
	d->data.len = len;
	d->data.buf = addr;
	return 0;
}