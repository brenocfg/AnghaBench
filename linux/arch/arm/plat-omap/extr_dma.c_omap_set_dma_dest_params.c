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
typedef  int u32 ;
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_write ) (int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CDEI ; 
 int /*<<< orphan*/  CDFI ; 
 int /*<<< orphan*/  CDSA ; 
 int /*<<< orphan*/  CSDP ; 
 scalar_t__ dma_omap1 () ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ,int) ; 
 int stub3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (int,int /*<<< orphan*/ ,int) ; 

void omap_set_dma_dest_params(int lch, int dest_port, int dest_amode,
			      unsigned long dest_start,
			      int dst_ei, int dst_fi)
{
	u32 l;

	if (dma_omap1()) {
		l = p->dma_read(CSDP, lch);
		l &= ~(0x1f << 9);
		l |= dest_port << 9;
		p->dma_write(l, CSDP, lch);
	}

	l = p->dma_read(CCR, lch);
	l &= ~(0x03 << 14);
	l |= dest_amode << 14;
	p->dma_write(l, CCR, lch);

	p->dma_write(dest_start, CDSA, lch);

	p->dma_write(dst_ei, CDEI, lch);
	p->dma_write(dst_fi, CDFI, lch);
}