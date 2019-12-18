#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u_int8_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
struct mvfrey_outlist_entry {int dummy; } ;
struct mvfrey_inlist_entry {int dummy; } ;
struct TYPE_5__ {int list_count; int inlist_phy; int outlist_phy; int* outlist_cptr; int outlist_cptr_phy; struct mvfrey_outlist_entry* outlist; struct mvfrey_inlist_entry* inlist; } ;
struct TYPE_6__ {TYPE_1__ mvfrey; } ;
struct hpt_iop_hba {char* ctlcfg_ptr; int ctlcfgcmd_phy; TYPE_2__ u; } ;
struct TYPE_7__ {scalar_t__ ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void hptiop_mvfrey_map_ctlcfg(void *arg, bus_dma_segment_t *segs,
				int nsegs, int error)
{
	struct hpt_iop_hba *hba = (struct hpt_iop_hba *)arg;
	char *p;
	u_int64_t phy;
	u_int32_t list_count = hba->u.mvfrey.list_count;

	phy = ((u_int64_t)segs->ds_addr + 0x1F) 
				& ~(u_int64_t)0x1F;
	p = (u_int8_t *)(((unsigned long)hba->ctlcfg_ptr + 0x1F)
				& ~0x1F);
	
	hba->ctlcfgcmd_phy = phy;
	hba->ctlcfg_ptr = p;

	p += 0x800;
	phy += 0x800;

	hba->u.mvfrey.inlist = (struct mvfrey_inlist_entry *)p;
	hba->u.mvfrey.inlist_phy = phy;

	p += list_count * sizeof(struct mvfrey_inlist_entry);
	phy += list_count * sizeof(struct mvfrey_inlist_entry);

	hba->u.mvfrey.outlist = (struct mvfrey_outlist_entry *)p;
	hba->u.mvfrey.outlist_phy = phy;

	p += list_count * sizeof(struct mvfrey_outlist_entry);
	phy += list_count * sizeof(struct mvfrey_outlist_entry);

	hba->u.mvfrey.outlist_cptr = (u_int32_t *)p;
	hba->u.mvfrey.outlist_cptr_phy = phy;
}