#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vm_flags; int /*<<< orphan*/  vm_parm; int /*<<< orphan*/  vm_parm_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  loadparm; } ;
struct ipl_parameter_block {TYPE_2__ ccw; } ;
struct TYPE_5__ {int vm_flags; int /*<<< orphan*/ * vm_parm; int /*<<< orphan*/  vm_parm_len; } ;
struct TYPE_8__ {TYPE_1__ ccw; } ;
struct TYPE_7__ {int /*<<< orphan*/  loadparm; scalar_t__ is_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG308_VMPARM_SIZE ; 
 int IPL_PB0_CCW_VM_FLAG_VP ; 
 int /*<<< orphan*/  IPL_PB0_FLAG_LOADPARM ; 
 int /*<<< orphan*/  LOADPARM_LEN ; 
 scalar_t__ MACHINE_IS_VM ; 
 TYPE_4__ ipl_block ; 
 scalar_t__ ipl_block_valid ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ sclp_ipl_info ; 

__attribute__((used)) static void reipl_block_ccw_fill_parms(struct ipl_parameter_block *ipb)
{
	/* LOADPARM */
	/* check if read scp info worked and set loadparm */
	if (sclp_ipl_info.is_valid)
		memcpy(ipb->ccw.loadparm, &sclp_ipl_info.loadparm, LOADPARM_LEN);
	else
		/* read scp info failed: set empty loadparm (EBCDIC blanks) */
		memset(ipb->ccw.loadparm, 0x40, LOADPARM_LEN);
	ipb->ccw.flags = IPL_PB0_FLAG_LOADPARM;

	/* VM PARM */
	if (MACHINE_IS_VM && ipl_block_valid &&
	    (ipl_block.ccw.vm_flags & IPL_PB0_CCW_VM_FLAG_VP)) {

		ipb->ccw.vm_flags |= IPL_PB0_CCW_VM_FLAG_VP;
		ipb->ccw.vm_parm_len = ipl_block.ccw.vm_parm_len;
		memcpy(ipb->ccw.vm_parm,
		       ipl_block.ccw.vm_parm, DIAG308_VMPARM_SIZE);
	}
}