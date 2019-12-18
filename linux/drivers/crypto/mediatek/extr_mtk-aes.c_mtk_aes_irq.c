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
typedef  int u32 ;
struct mtk_cryp {int /*<<< orphan*/  dev; } ;
struct mtk_aes_rec {int flags; int /*<<< orphan*/  done_task; int /*<<< orphan*/  id; struct mtk_cryp* cryp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AES_FLAGS_BUSY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MTK_CNT_RST ; 
 int MTK_RDR_PROC_MODE ; 
 int MTK_RDR_PROC_THRESH ; 
 int /*<<< orphan*/  RDR_PROC_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDR_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDR_THRESH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ likely (int) ; 
 int mtk_aes_read (struct mtk_cryp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_aes_write (struct mtk_cryp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mtk_aes_irq(int irq, void *dev_id)
{
	struct mtk_aes_rec *aes  = (struct mtk_aes_rec *)dev_id;
	struct mtk_cryp *cryp = aes->cryp;
	u32 val = mtk_aes_read(cryp, RDR_STAT(aes->id));

	mtk_aes_write(cryp, RDR_STAT(aes->id), val);

	if (likely(AES_FLAGS_BUSY & aes->flags)) {
		mtk_aes_write(cryp, RDR_PROC_COUNT(aes->id), MTK_CNT_RST);
		mtk_aes_write(cryp, RDR_THRESH(aes->id),
			      MTK_RDR_PROC_THRESH | MTK_RDR_PROC_MODE);

		tasklet_schedule(&aes->done_task);
	} else {
		dev_warn(cryp->dev, "AES interrupt when no active requests.\n");
	}
	return IRQ_HANDLED;
}