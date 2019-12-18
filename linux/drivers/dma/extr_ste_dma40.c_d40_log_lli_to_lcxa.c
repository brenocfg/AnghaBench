#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct d40_log_lli_bidir {int /*<<< orphan*/ * src; int /*<<< orphan*/ * dst; } ;
struct d40_log_lli {int dummy; } ;
struct d40_lcla_pool {int /*<<< orphan*/  dma_addr; struct d40_log_lli* base; } ;
struct d40_desc {int lli_current; int lli_len; int cyclic; struct d40_log_lli_bidir lli_log; } ;
struct TYPE_6__ {scalar_t__ dir; } ;
struct d40_chan {TYPE_4__* base; int /*<<< orphan*/  lcpa; TYPE_3__* phy_chan; TYPE_2__ dma_cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; TYPE_1__* plat_data; struct d40_lcla_pool lcla_pool; } ;
struct TYPE_7__ {int num; scalar_t__ use_soft_lli; } ;
struct TYPE_5__ {int use_esram_lcla; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 unsigned int LLI_TERM_INT ; 
 int d40_lcla_alloc_one (struct d40_chan*,struct d40_desc*) ; 
 int /*<<< orphan*/  d40_log_lli_lcla_write (struct d40_log_lli*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  d40_log_lli_lcpa_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d40_log_lli_to_lcxa(struct d40_chan *chan, struct d40_desc *desc)
{
	struct d40_lcla_pool *pool = &chan->base->lcla_pool;
	struct d40_log_lli_bidir *lli = &desc->lli_log;
	int lli_current = desc->lli_current;
	int lli_len = desc->lli_len;
	bool cyclic = desc->cyclic;
	int curr_lcla = -EINVAL;
	int first_lcla = 0;
	bool use_esram_lcla = chan->base->plat_data->use_esram_lcla;
	bool linkback;

	/*
	 * We may have partially running cyclic transfers, in case we did't get
	 * enough LCLA entries.
	 */
	linkback = cyclic && lli_current == 0;

	/*
	 * For linkback, we need one LCLA even with only one link, because we
	 * can't link back to the one in LCPA space
	 */
	if (linkback || (lli_len - lli_current > 1)) {
		/*
		 * If the channel is expected to use only soft_lli don't
		 * allocate a lcla. This is to avoid a HW issue that exists
		 * in some controller during a peripheral to memory transfer
		 * that uses linked lists.
		 */
		if (!(chan->phy_chan->use_soft_lli &&
			chan->dma_cfg.dir == DMA_DEV_TO_MEM))
			curr_lcla = d40_lcla_alloc_one(chan, desc);

		first_lcla = curr_lcla;
	}

	/*
	 * For linkback, we normally load the LCPA in the loop since we need to
	 * link it to the second LCLA and not the first.  However, if we
	 * couldn't even get a first LCLA, then we have to run in LCPA and
	 * reload manually.
	 */
	if (!linkback || curr_lcla == -EINVAL) {
		unsigned int flags = 0;

		if (curr_lcla == -EINVAL)
			flags |= LLI_TERM_INT;

		d40_log_lli_lcpa_write(chan->lcpa,
				       &lli->dst[lli_current],
				       &lli->src[lli_current],
				       curr_lcla,
				       flags);
		lli_current++;
	}

	if (curr_lcla < 0)
		goto set_current;

	for (; lli_current < lli_len; lli_current++) {
		unsigned int lcla_offset = chan->phy_chan->num * 1024 +
					   8 * curr_lcla * 2;
		struct d40_log_lli *lcla = pool->base + lcla_offset;
		unsigned int flags = 0;
		int next_lcla;

		if (lli_current + 1 < lli_len)
			next_lcla = d40_lcla_alloc_one(chan, desc);
		else
			next_lcla = linkback ? first_lcla : -EINVAL;

		if (cyclic || next_lcla == -EINVAL)
			flags |= LLI_TERM_INT;

		if (linkback && curr_lcla == first_lcla) {
			/* First link goes in both LCPA and LCLA */
			d40_log_lli_lcpa_write(chan->lcpa,
					       &lli->dst[lli_current],
					       &lli->src[lli_current],
					       next_lcla, flags);
		}

		/*
		 * One unused LCLA in the cyclic case if the very first
		 * next_lcla fails...
		 */
		d40_log_lli_lcla_write(lcla,
				       &lli->dst[lli_current],
				       &lli->src[lli_current],
				       next_lcla, flags);

		/*
		 * Cache maintenance is not needed if lcla is
		 * mapped in esram
		 */
		if (!use_esram_lcla) {
			dma_sync_single_range_for_device(chan->base->dev,
						pool->dma_addr, lcla_offset,
						2 * sizeof(struct d40_log_lli),
						DMA_TO_DEVICE);
		}
		curr_lcla = next_lcla;

		if (curr_lcla == -EINVAL || curr_lcla == first_lcla) {
			lli_current++;
			break;
		}
	}
 set_current:
	desc->lli_current = lli_current;
}