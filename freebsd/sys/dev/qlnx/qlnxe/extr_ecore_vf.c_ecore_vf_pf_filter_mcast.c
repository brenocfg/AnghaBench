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
typedef  int u32 ;
struct ecore_sp_vport_update_params {int update_approx_mcast_flg; int* bins; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_filter_mcast {scalar_t__ opcode; int num_mc_addrs; int /*<<< orphan*/ * mac; } ;
typedef  int /*<<< orphan*/  sp_params ;

/* Variables and functions */
 scalar_t__ ECORE_FILTER_ADD ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_vport_update_params*,int /*<<< orphan*/ ,int) ; 
 int ecore_mcast_bin_from_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_vf_pf_vport_update (struct ecore_hwfn*,struct ecore_sp_vport_update_params*) ; 

void ecore_vf_pf_filter_mcast(struct ecore_hwfn *p_hwfn,
			      struct ecore_filter_mcast *p_filter_cmd)
{
	struct ecore_sp_vport_update_params sp_params;
	int i;

	OSAL_MEMSET(&sp_params, 0, sizeof(sp_params));
	sp_params.update_approx_mcast_flg = 1;

	if (p_filter_cmd->opcode == ECORE_FILTER_ADD) {
		for (i = 0; i < p_filter_cmd->num_mc_addrs; i++) {
			u32 bit;

			bit = ecore_mcast_bin_from_mac(p_filter_cmd->mac[i]);
			sp_params.bins[bit / 32] |= 1 << (bit % 32);
		}
	}

	ecore_vf_pf_vport_update(p_hwfn, &sp_params);
}