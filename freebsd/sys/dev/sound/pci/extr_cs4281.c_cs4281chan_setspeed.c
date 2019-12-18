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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sc_info {int dummy; } ;
struct sc_chinfo {scalar_t__ dma_chan; int /*<<< orphan*/  spd; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_ADCSR ; 
 int /*<<< orphan*/  CS4281PCI_DACSR ; 
 scalar_t__ CS4281_DMA_PLAY ; 
 int /*<<< orphan*/  adcdac_go (struct sc_chinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_rate_to_rv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_rv_to_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
cs4281chan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
    struct sc_chinfo *ch = data;
    struct sc_info *sc = ch->parent;
    u_int32_t go, v, r;

    go = adcdac_go(ch, 0); /* pause */
    r = (ch->dma_chan == CS4281_DMA_PLAY) ? CS4281PCI_DACSR : CS4281PCI_ADCSR;
    v = cs4281_rate_to_rv(speed);
    cs4281_wr(sc, r, v);
    adcdac_go(ch, go); /* unpause */

    ch->spd = cs4281_rv_to_rate(v);
    return ch->spd;
}