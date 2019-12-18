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
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ecore_rdma_free_ilt (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_rdma_free_reserved_lkey (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_rdma_resc_free (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_rdma_free(struct ecore_hwfn *p_hwfn)
{
	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "\n");

	ecore_rdma_free_reserved_lkey(p_hwfn);

	ecore_rdma_resc_free(p_hwfn);

	ecore_rdma_free_ilt(p_hwfn);
}