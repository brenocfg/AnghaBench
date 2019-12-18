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
typedef  int u_int32_t ;
struct sc_info {int dummy; } ;
struct sc_chinfo {int /*<<< orphan*/  dma_chan; struct sc_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_DCR (int /*<<< orphan*/ ) ; 
 int CS4281PCI_DCR_MSK ; 
 int /*<<< orphan*/  CS4281PCI_HICR ; 
 int /*<<< orphan*/  CS4281PCI_HICR_EOI ; 
 int /*<<< orphan*/  cs4281_clr4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int cs4281_rd (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_set4 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
adcdac_go(struct sc_chinfo *ch, u_int32_t go)
{
    struct sc_info *sc = ch->parent;
    u_int32_t going;

    going = !(cs4281_rd(sc, CS4281PCI_DCR(ch->dma_chan)) & CS4281PCI_DCR_MSK);

    if (go)
	cs4281_clr4(sc, CS4281PCI_DCR(ch->dma_chan), CS4281PCI_DCR_MSK);
    else
	cs4281_set4(sc, CS4281PCI_DCR(ch->dma_chan), CS4281PCI_DCR_MSK);

    cs4281_wr(sc, CS4281PCI_HICR, CS4281PCI_HICR_EOI);

    return going;
}