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
struct mtk_uart_apdmadev {scalar_t__ support_33bits; } ;
struct mtk_uart_apdma_desc {unsigned int addr; } ;
struct TYPE_6__ {TYPE_4__* device; } ;
struct TYPE_7__ {TYPE_2__ chan; } ;
struct TYPE_5__ {unsigned int src_port_window_size; } ;
struct mtk_chan {TYPE_3__ vc; TYPE_1__ cfg; struct mtk_uart_apdma_desc* desc; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int VFF_4G_EN_B ; 
 int /*<<< orphan*/  VFF_4G_SUPPORT ; 
 int /*<<< orphan*/  VFF_ADDR ; 
 int /*<<< orphan*/  VFF_EN ; 
 unsigned int VFF_EN_B ; 
 int /*<<< orphan*/  VFF_INT_EN ; 
 int /*<<< orphan*/  VFF_INT_FLAG ; 
 int /*<<< orphan*/  VFF_LEN ; 
 int /*<<< orphan*/  VFF_RPT ; 
 unsigned int VFF_RX_INT_CLR_B ; 
 unsigned int VFF_RX_INT_EN_B ; 
 unsigned int VFF_RX_THRE (unsigned int) ; 
 int /*<<< orphan*/  VFF_THRE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int mtk_uart_apdma_read (struct mtk_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_uart_apdma_write (struct mtk_chan*,int /*<<< orphan*/ ,unsigned int) ; 
 struct mtk_uart_apdmadev* to_mtk_uart_apdma_dev (TYPE_4__*) ; 

__attribute__((used)) static void mtk_uart_apdma_start_rx(struct mtk_chan *c)
{
	struct mtk_uart_apdmadev *mtkd =
				to_mtk_uart_apdma_dev(c->vc.chan.device);
	struct mtk_uart_apdma_desc *d = c->desc;
	unsigned int vff_sz;

	vff_sz = c->cfg.src_port_window_size;
	if (!mtk_uart_apdma_read(c, VFF_LEN)) {
		mtk_uart_apdma_write(c, VFF_ADDR, d->addr);
		mtk_uart_apdma_write(c, VFF_LEN, vff_sz);
		mtk_uart_apdma_write(c, VFF_THRE, VFF_RX_THRE(vff_sz));
		mtk_uart_apdma_write(c, VFF_RPT, 0);
		mtk_uart_apdma_write(c, VFF_INT_FLAG, VFF_RX_INT_CLR_B);

		if (mtkd->support_33bits)
			mtk_uart_apdma_write(c, VFF_4G_SUPPORT, VFF_4G_EN_B);
	}

	mtk_uart_apdma_write(c, VFF_INT_EN, VFF_RX_INT_EN_B);
	mtk_uart_apdma_write(c, VFF_EN, VFF_EN_B);
	if (mtk_uart_apdma_read(c, VFF_EN) != VFF_EN_B)
		dev_err(c->vc.chan.device->dev, "Enable RX fail\n");
}