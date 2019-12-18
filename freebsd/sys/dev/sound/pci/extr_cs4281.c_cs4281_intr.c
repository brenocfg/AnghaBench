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
typedef  int u_int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct sc_info {TYPE_2__ rch; TYPE_1__ pch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_HDSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4281PCI_HICR ; 
 int /*<<< orphan*/  CS4281PCI_HICR_EOI ; 
 int /*<<< orphan*/  CS4281PCI_HISR ; 
 int CS4281PCI_HISR_DMA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4281_DMA_PLAY ; 
 int /*<<< orphan*/  CS4281_DMA_REC ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int cs4281_rd (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cs4281_intr(void *p)
{
    struct sc_info *sc = (struct sc_info *)p;
    u_int32_t hisr;

    hisr = cs4281_rd(sc, CS4281PCI_HISR);

    if (hisr == 0) return;

    if (hisr & CS4281PCI_HISR_DMA(CS4281_DMA_PLAY)) {
	chn_intr(sc->pch.channel);
	cs4281_rd(sc, CS4281PCI_HDSR(CS4281_DMA_PLAY)); /* Clear interrupt */
    }

    if (hisr & CS4281PCI_HISR_DMA(CS4281_DMA_REC)) {
	chn_intr(sc->rch.channel);
	cs4281_rd(sc, CS4281PCI_HDSR(CS4281_DMA_REC)); /* Clear interrupt */
    }

    /* Signal End-of-Interrupt */
    cs4281_wr(sc, CS4281PCI_HICR, CS4281PCI_HICR_EOI);
}