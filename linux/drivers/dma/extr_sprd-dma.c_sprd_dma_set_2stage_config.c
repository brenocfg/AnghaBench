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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct sprd_dma_dev {TYPE_2__ dma_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct sprd_dma_chn {int chn_num; int chn_mode; int /*<<< orphan*/  int_type; int /*<<< orphan*/  trg_mode; TYPE_1__ vc; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  SPRD_DMA_DST_CHN0 131 
#define  SPRD_DMA_DST_CHN1 130 
 int SPRD_DMA_GLB_2STAGE_EN ; 
 int /*<<< orphan*/  SPRD_DMA_GLB_2STAGE_GRP1 ; 
 int /*<<< orphan*/  SPRD_DMA_GLB_2STAGE_GRP2 ; 
 int SPRD_DMA_GLB_DEST_CHN_MASK ; 
 int SPRD_DMA_GLB_DEST_CHN_OFFSET ; 
 int SPRD_DMA_GLB_DEST_INT ; 
 int SPRD_DMA_GLB_SRC_CHN_MASK ; 
 int SPRD_DMA_GLB_SRC_INT ; 
 int SPRD_DMA_GLB_TRG_OFFSET ; 
 int /*<<< orphan*/  SPRD_DMA_NO_INT ; 
#define  SPRD_DMA_SRC_CHN0 129 
#define  SPRD_DMA_SRC_CHN1 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sprd_dma_glb_update (struct sprd_dma_dev*,int /*<<< orphan*/ ,int,int) ; 
 struct sprd_dma_dev* to_sprd_dma_dev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_dma_set_2stage_config(struct sprd_dma_chn *schan)
{
	struct sprd_dma_dev *sdev = to_sprd_dma_dev(&schan->vc.chan);
	u32 val, chn = schan->chn_num + 1;

	switch (schan->chn_mode) {
	case SPRD_DMA_SRC_CHN0:
		val = chn & SPRD_DMA_GLB_SRC_CHN_MASK;
		val |= BIT(schan->trg_mode - 1) << SPRD_DMA_GLB_TRG_OFFSET;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		if (schan->int_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_SRC_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP1, val, val);
		break;

	case SPRD_DMA_SRC_CHN1:
		val = chn & SPRD_DMA_GLB_SRC_CHN_MASK;
		val |= BIT(schan->trg_mode - 1) << SPRD_DMA_GLB_TRG_OFFSET;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		if (schan->int_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_SRC_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP2, val, val);
		break;

	case SPRD_DMA_DST_CHN0:
		val = (chn << SPRD_DMA_GLB_DEST_CHN_OFFSET) &
			SPRD_DMA_GLB_DEST_CHN_MASK;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		if (schan->int_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_DEST_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP1, val, val);
		break;

	case SPRD_DMA_DST_CHN1:
		val = (chn << SPRD_DMA_GLB_DEST_CHN_OFFSET) &
			SPRD_DMA_GLB_DEST_CHN_MASK;
		val |= SPRD_DMA_GLB_2STAGE_EN;
		if (schan->int_type != SPRD_DMA_NO_INT)
			val |= SPRD_DMA_GLB_DEST_INT;

		sprd_dma_glb_update(sdev, SPRD_DMA_GLB_2STAGE_GRP2, val, val);
		break;

	default:
		dev_err(sdev->dma_dev.dev, "invalid channel mode setting %d\n",
			schan->chn_mode);
		return -EINVAL;
	}

	return 0;
}