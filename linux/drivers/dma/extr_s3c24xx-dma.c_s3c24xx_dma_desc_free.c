#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct s3c24xx_txd {int dummy; } ;
struct s3c24xx_dma_chan {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_descriptor_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  s3c24xx_dma_free_txd (struct s3c24xx_txd*) ; 
 struct s3c24xx_dma_chan* to_s3c24xx_dma_chan (int /*<<< orphan*/ ) ; 
 struct s3c24xx_txd* to_s3c24xx_txd (TYPE_1__*) ; 

__attribute__((used)) static void s3c24xx_dma_desc_free(struct virt_dma_desc *vd)
{
	struct s3c24xx_txd *txd = to_s3c24xx_txd(&vd->tx);
	struct s3c24xx_dma_chan *s3cchan = to_s3c24xx_dma_chan(vd->tx.chan);

	if (!s3cchan->slave)
		dma_descriptor_unmap(&vd->tx);

	s3c24xx_dma_free_txd(txd);
}