#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct amr_sgentry {int sg_addr; int /*<<< orphan*/  sg_count; } ;
struct amr_sg64entry {int sg_addr; int /*<<< orphan*/  sg_count; } ;
struct TYPE_4__ {struct amr_sg64entry* sg64; struct amr_sgentry* sg32; } ;
struct amr_command {int ac_nsegments; int ac_mb_physaddr; int ac_sgbusaddr; int ac_flags; int /*<<< orphan*/  ac_datamap; int /*<<< orphan*/  ac_tag; TYPE_1__ ac_sg; } ;
struct TYPE_5__ {int ds_addr; int /*<<< orphan*/  ds_len; } ;
typedef  TYPE_2__ bus_dma_segment_t ;

/* Variables and functions */
 scalar_t__ AC_IS_SG64 (struct amr_command*) ; 
 int AMR_CMD_DATAIN ; 
 int AMR_CMD_DATAOUT ; 
 int AMR_CMD_MAPPED ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
amr_setup_sg(void *arg, bus_dma_segment_t *segs, int nsegments, int error)
{
    struct amr_command	*ac = (struct amr_command *)arg;
    struct amr_sgentry	*sg;
    struct amr_sg64entry *sg64;
    int flags, i;

    debug_called(3);

    /* get base address of s/g table */
    sg = ac->ac_sg.sg32;
    sg64 = ac->ac_sg.sg64;

    if (AC_IS_SG64(ac)) {
	ac->ac_nsegments = nsegments;
	ac->ac_mb_physaddr = 0xffffffff;
	for (i = 0; i < nsegments; i++, sg64++) {
	    sg64->sg_addr = segs[i].ds_addr;
	    sg64->sg_count = segs[i].ds_len;
	}
    } else {
	/* decide whether we need to populate the s/g table */
	if (nsegments < 2) {
	    ac->ac_nsegments = 0;
	    ac->ac_mb_physaddr = segs[0].ds_addr;
	} else {
            ac->ac_nsegments = nsegments;
	    ac->ac_mb_physaddr = ac->ac_sgbusaddr;
	    for (i = 0; i < nsegments; i++, sg++) {
		sg->sg_addr = segs[i].ds_addr;
		sg->sg_count = segs[i].ds_len;
	    }
	}
    }

    flags = 0;
    if (ac->ac_flags & AMR_CMD_DATAIN)
	flags |= BUS_DMASYNC_PREREAD;
    if (ac->ac_flags & AMR_CMD_DATAOUT)
	flags |= BUS_DMASYNC_PREWRITE;
    bus_dmamap_sync(ac->ac_tag, ac->ac_datamap, flags);
    ac->ac_flags |= AMR_CMD_MAPPED;
}