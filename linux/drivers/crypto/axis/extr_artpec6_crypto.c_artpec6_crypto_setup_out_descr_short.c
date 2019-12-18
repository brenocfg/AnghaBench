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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int short_descr; unsigned int short_len; int eop; } ;
struct pdma_descr {TYPE_2__ shrt; TYPE_1__ ctrl; } ;
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_descriptors {scalar_t__ out_cnt; struct pdma_descr* out; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ PDMA_DESCR_COUNT ; 
 scalar_t__ fault_inject_dma_descr () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct pdma_descr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
artpec6_crypto_setup_out_descr_short(struct artpec6_crypto_req_common *common,
				     void *dst, unsigned int len, bool eop)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;
	struct pdma_descr *d;

	if (dma->out_cnt >= PDMA_DESCR_COUNT ||
	    fault_inject_dma_descr()) {
		pr_err("No free OUT DMA descriptors available!\n");
		return -ENOSPC;
	} else if (len > 7 || len < 1) {
		return -EINVAL;
	}
	d = &dma->out[dma->out_cnt++];
	memset(d, 0, sizeof(*d));

	d->ctrl.short_descr = 1;
	d->ctrl.short_len = len;
	d->ctrl.eop = eop;
	memcpy(d->shrt.data, dst, len);
	return 0;
}