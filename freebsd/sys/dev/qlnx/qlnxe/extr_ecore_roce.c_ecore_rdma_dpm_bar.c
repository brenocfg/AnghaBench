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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int db_bar_no_edpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_rdma_dpm_conf (struct ecore_hwfn*,struct ecore_ptt*) ; 

void ecore_rdma_dpm_bar(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt)
{
	p_hwfn->db_bar_no_edpm = true;

	ecore_rdma_dpm_conf(p_hwfn, p_ptt);
}