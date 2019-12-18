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
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct s3c24xx_txd {TYPE_1__ dsg_list; int /*<<< orphan*/  at; TYPE_2__ vd; } ;
struct s3c24xx_dma_phy {int dummy; } ;
struct s3c24xx_dma_chan {struct s3c24xx_txd* at; int /*<<< orphan*/  vc; struct s3c24xx_dma_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ s3c24xx_dma_phy_busy (struct s3c24xx_dma_phy*) ; 
 int /*<<< orphan*/  s3c24xx_dma_start_next_sg (struct s3c24xx_dma_chan*,struct s3c24xx_txd*) ; 
 struct s3c24xx_txd* to_s3c24xx_txd (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3c24xx_dma_start_next_txd(struct s3c24xx_dma_chan *s3cchan)
{
	struct s3c24xx_dma_phy *phy = s3cchan->phy;
	struct virt_dma_desc *vd = vchan_next_desc(&s3cchan->vc);
	struct s3c24xx_txd *txd = to_s3c24xx_txd(&vd->tx);

	list_del(&txd->vd.node);

	s3cchan->at = txd;

	/* Wait for channel inactive */
	while (s3c24xx_dma_phy_busy(phy))
		cpu_relax();

	/* point to the first element of the sg list */
	txd->at = txd->dsg_list.next;
	s3c24xx_dma_start_next_sg(s3cchan, txd);
}