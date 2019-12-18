#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mly_softc {scalar_t__ mly_sg_busaddr; struct mly_sg_entry* mly_sg_table; } ;
struct mly_sg_entry {int /*<<< orphan*/  length; int /*<<< orphan*/  physaddr; } ;
struct TYPE_12__ {int extended_sg_table; } ;
struct TYPE_10__ {int* entries; scalar_t__* table_physaddr; } ;
struct TYPE_9__ {struct mly_sg_entry* sg; } ;
struct TYPE_11__ {TYPE_3__ indirect; TYPE_2__ direct; } ;
struct mly_command_generic {TYPE_5__ command_control; TYPE_4__ transfer; } ;
struct mly_command {int mc_slot; TYPE_1__* mc_packet; struct mly_softc* mc_sc; } ;
struct TYPE_13__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_6__ bus_dma_segment_t ;
struct TYPE_8__ {struct mly_command_generic generic; } ;

/* Variables and functions */
 int MLY_MAX_SGENTRIES ; 
 int MLY_SLOT_START ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
mly_map_command_sg(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
    struct mly_command		*mc = (struct mly_command *)arg;
    struct mly_softc		*sc = mc->mc_sc;
    struct mly_command_generic	*gen = &(mc->mc_packet->generic);
    struct mly_sg_entry		*sg;
    int				i, tabofs;

    debug_called(2);

    /* can we use the transfer structure directly? */
    if (nseg <= 2) {
	sg = &gen->transfer.direct.sg[0];
	gen->command_control.extended_sg_table = 0;
    } else {
	tabofs = ((mc->mc_slot - MLY_SLOT_START) * MLY_MAX_SGENTRIES);
	sg = sc->mly_sg_table + tabofs;
	gen->transfer.indirect.entries[0] = nseg;
	gen->transfer.indirect.table_physaddr[0] = sc->mly_sg_busaddr + (tabofs * sizeof(struct mly_sg_entry));
	gen->command_control.extended_sg_table = 1;
    }

    /* copy the s/g table */
    for (i = 0; i < nseg; i++) {
	sg[i].physaddr = segs[i].ds_addr;
	sg[i].length = segs[i].ds_len;
    }

}