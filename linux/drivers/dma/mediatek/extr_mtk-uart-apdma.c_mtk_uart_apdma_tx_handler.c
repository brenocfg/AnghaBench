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
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct mtk_uart_apdma_desc {TYPE_1__ vd; } ;
struct mtk_chan {struct mtk_uart_apdma_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFF_EN ; 
 int /*<<< orphan*/  VFF_EN_CLR_B ; 
 int /*<<< orphan*/  VFF_INT_EN ; 
 int /*<<< orphan*/  VFF_INT_EN_CLR_B ; 
 int /*<<< orphan*/  VFF_INT_FLAG ; 
 int /*<<< orphan*/  VFF_TX_INT_CLR_B ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_uart_apdma_write (struct mtk_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_1__*) ; 

__attribute__((used)) static void mtk_uart_apdma_tx_handler(struct mtk_chan *c)
{
	struct mtk_uart_apdma_desc *d = c->desc;

	mtk_uart_apdma_write(c, VFF_INT_FLAG, VFF_TX_INT_CLR_B);
	mtk_uart_apdma_write(c, VFF_INT_EN, VFF_INT_EN_CLR_B);
	mtk_uart_apdma_write(c, VFF_EN, VFF_EN_CLR_B);

	list_del(&d->vd.node);
	vchan_cookie_complete(&d->vd);
}