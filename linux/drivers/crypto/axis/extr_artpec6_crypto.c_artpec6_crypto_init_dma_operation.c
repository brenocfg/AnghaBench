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
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_descriptors {int /*<<< orphan*/  bounce_buffers; scalar_t__ map_count; scalar_t__ in_cnt; scalar_t__ out_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
artpec6_crypto_init_dma_operation(struct artpec6_crypto_req_common *common)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;

	dma->out_cnt = 0;
	dma->in_cnt = 0;
	dma->map_count = 0;
	INIT_LIST_HEAD(&dma->bounce_buffers);
}