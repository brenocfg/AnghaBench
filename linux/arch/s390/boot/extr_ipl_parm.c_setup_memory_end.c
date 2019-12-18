#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ opt; } ;
struct TYPE_4__ {scalar_t__ pbt; } ;
struct TYPE_6__ {TYPE_2__ fcp; TYPE_1__ pb0_hdr; } ;

/* Variables and functions */
 scalar_t__ IPL_PB0_FCP_OPT_DUMP ; 
 scalar_t__ IPL_PBT_FCP ; 
 scalar_t__ OLDMEM_BASE ; 
 TYPE_3__ ipl_block ; 
 scalar_t__ ipl_block_valid ; 
 scalar_t__ kaslr_enabled ; 
 scalar_t__ memory_end ; 
 int memory_end_set ; 
 int /*<<< orphan*/  sclp_early_get_hsa_size (scalar_t__*) ; 

void setup_memory_end(void)
{
#ifdef CONFIG_CRASH_DUMP
	if (OLDMEM_BASE) {
		kaslr_enabled = 0;
	} else if (ipl_block_valid &&
		   ipl_block.pb0_hdr.pbt == IPL_PBT_FCP &&
		   ipl_block.fcp.opt == IPL_PB0_FCP_OPT_DUMP) {
		kaslr_enabled = 0;
		if (!sclp_early_get_hsa_size(&memory_end) && memory_end)
			memory_end_set = 1;
	}
#endif
}