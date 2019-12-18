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
struct sc_chinfo {int dma_setup; int bps; int /*<<< orphan*/  buffer; int /*<<< orphan*/  dma_chan; struct sc_info* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_DBA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4281PCI_DBC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adcdac_go (struct sc_chinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4281_wr (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adcdac_prog(struct sc_chinfo *ch)
{
    struct sc_info *sc = ch->parent;
    u_int32_t go;

    if (!ch->dma_setup) {
	go = adcdac_go(ch, 0);
	cs4281_wr(sc, CS4281PCI_DBA(ch->dma_chan),
		  sndbuf_getbufaddr(ch->buffer));
	cs4281_wr(sc, CS4281PCI_DBC(ch->dma_chan),
		  sndbuf_getsize(ch->buffer) / ch->bps - 1);
	ch->dma_setup = 1;
	adcdac_go(ch, go);
    }
}