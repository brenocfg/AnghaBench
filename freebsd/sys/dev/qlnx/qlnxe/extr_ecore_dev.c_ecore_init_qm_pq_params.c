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
 int /*<<< orphan*/  ecore_init_qm_advance_vport (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_lb_pq (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_low_latency_pq (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_mcos_pqs (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_offload_pq (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_ooo_pq (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_pure_ack_pq (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_rl_pqs (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_vf_pqs (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_init_qm_pq_params(struct ecore_hwfn *p_hwfn)
{
	/* rate limited pqs, must come first (FW assumption) */
	ecore_init_qm_rl_pqs(p_hwfn);

	/* pqs for multi cos */
	ecore_init_qm_mcos_pqs(p_hwfn);

	/* pure loopback pq */
	ecore_init_qm_lb_pq(p_hwfn);

	/* out of order pq */
	ecore_init_qm_ooo_pq(p_hwfn);

	/* pure ack pq */
	ecore_init_qm_pure_ack_pq(p_hwfn);

	/* pq for offloaded protocol */
	ecore_init_qm_offload_pq(p_hwfn);

	/* low latency pq */
	ecore_init_qm_low_latency_pq(p_hwfn);

	/* done sharing vports */
	ecore_init_qm_advance_vport(p_hwfn);

	/* pqs for vfs */
	ecore_init_qm_vf_pqs(p_hwfn);
}