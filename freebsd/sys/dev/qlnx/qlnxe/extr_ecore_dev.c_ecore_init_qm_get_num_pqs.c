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
typedef  int u16 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int PQ_FLAGS_ACK ; 
 int PQ_FLAGS_LB ; 
 int PQ_FLAGS_LLT ; 
 int PQ_FLAGS_MCOS ; 
 int PQ_FLAGS_OFLD ; 
 int PQ_FLAGS_OOO ; 
 int PQ_FLAGS_RLS ; 
 int PQ_FLAGS_VFS ; 
 int ecore_get_pq_flags (struct ecore_hwfn*) ; 
 int ecore_init_qm_get_num_pf_rls (struct ecore_hwfn*) ; 
 int ecore_init_qm_get_num_tcs (struct ecore_hwfn*) ; 
 int ecore_init_qm_get_num_vfs (struct ecore_hwfn*) ; 

u16 ecore_init_qm_get_num_pqs(struct ecore_hwfn *p_hwfn)
{
	u32 pq_flags = ecore_get_pq_flags(p_hwfn);

	return (!!(PQ_FLAGS_RLS & pq_flags)) * ecore_init_qm_get_num_pf_rls(p_hwfn) +
	       (!!(PQ_FLAGS_MCOS & pq_flags)) * ecore_init_qm_get_num_tcs(p_hwfn) +
	       (!!(PQ_FLAGS_LB & pq_flags)) +
	       (!!(PQ_FLAGS_OOO & pq_flags)) +
	       (!!(PQ_FLAGS_ACK & pq_flags)) +
	       (!!(PQ_FLAGS_OFLD & pq_flags)) +
	       (!!(PQ_FLAGS_LLT & pq_flags)) +
	       (!!(PQ_FLAGS_VFS & pq_flags)) * ecore_init_qm_get_num_vfs(p_hwfn);
}