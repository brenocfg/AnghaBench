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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIG_REG_VXLAN_CTRL ; 
 int /*<<< orphan*/  PBF_REG_VXLAN_PORT ; 
 int /*<<< orphan*/  PRS_REG_VXLAN_PORT ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ecore_set_vxlan_dest_port(struct ecore_hwfn *p_hwfn,
	struct ecore_ptt *p_ptt,
	u16 dest_port)
{
	/* Update PRS register */
	ecore_wr(p_hwfn, p_ptt, PRS_REG_VXLAN_PORT, dest_port);

	/* Update NIG register */
	ecore_wr(p_hwfn, p_ptt, NIG_REG_VXLAN_CTRL, dest_port);

	/* Update PBF register */
	ecore_wr(p_hwfn, p_ptt, PBF_REG_VXLAN_PORT, dest_port);
}