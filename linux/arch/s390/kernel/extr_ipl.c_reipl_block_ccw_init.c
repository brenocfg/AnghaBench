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
struct TYPE_4__ {int /*<<< orphan*/  pbt; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  version; int /*<<< orphan*/  len; } ;
struct ipl_parameter_block {TYPE_2__ pb0_hdr; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPL_BP0_CCW_LEN ; 
 int /*<<< orphan*/  IPL_BP_CCW_LEN ; 
 int /*<<< orphan*/  IPL_PARM_BLOCK_VERSION ; 
 int /*<<< orphan*/  IPL_PBT_CCW ; 

__attribute__((used)) static void reipl_block_ccw_init(struct ipl_parameter_block *ipb)
{
	ipb->hdr.len = IPL_BP_CCW_LEN;
	ipb->hdr.version = IPL_PARM_BLOCK_VERSION;
	ipb->pb0_hdr.len = IPL_BP0_CCW_LEN;
	ipb->pb0_hdr.pbt = IPL_PBT_CCW;
}