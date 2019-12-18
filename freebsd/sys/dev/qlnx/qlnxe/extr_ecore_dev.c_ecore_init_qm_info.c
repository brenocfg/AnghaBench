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
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_dp_init_qm_params (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_params (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_port_params (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_pq_params (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_reset_params (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_vport_params (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_init_qm_info(struct ecore_hwfn *p_hwfn)
{
	/* reset params required for init run */
	ecore_init_qm_reset_params(p_hwfn);

	/* init QM top level params */
	ecore_init_qm_params(p_hwfn);

	/* init QM port params */
	ecore_init_qm_port_params(p_hwfn);

	/* init QM vport params */
	ecore_init_qm_vport_params(p_hwfn);

	/* init QM physical queue params */
	ecore_init_qm_pq_params(p_hwfn);

	/* display all that init */
	ecore_dp_init_qm_params(p_hwfn);
}