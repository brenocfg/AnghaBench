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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ QM_OTHER_PQS_PER_PF ; 
 scalar_t__ QM_PF_QUEUE_GROUP_SIZE ; 
 scalar_t__ QM_PQ_MEM_4KB (scalar_t__) ; 
 scalar_t__ QM_PQ_SIZE_256B (scalar_t__) ; 
 scalar_t__ QM_REG_BASEADDROTHERPQ_RT_OFFSET ; 
 scalar_t__ QM_REG_MAXPQSIZE_2_RT_OFFSET ; 
 scalar_t__ QM_REG_PQOTHER2PF_0_RT_OFFSET ; 
 scalar_t__ QM_REG_PTRTBLOTHER_RT_OFFSET ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ecore_other_pq_map_rt_init(struct ecore_hwfn *p_hwfn,
									   u8 pf_id,
									   bool is_pf_loading,
									   u32 num_pf_cids,
									   u32 num_tids,
									   u32 base_mem_addr_4kb)
{
	u32 pq_size, pq_mem_4kb, mem_addr_4kb;
	u16 i, j, pq_id, pq_group;

	/* A single other PQ group is used in each PF, where PQ group i is used
	 * in PF i.
	 */
	pq_group = pf_id;
	pq_size = num_pf_cids + num_tids;
	pq_mem_4kb = QM_PQ_MEM_4KB(pq_size);
	mem_addr_4kb = base_mem_addr_4kb;

	/* Map PQ group to PF */
	STORE_RT_REG(p_hwfn, QM_REG_PQOTHER2PF_0_RT_OFFSET + pq_group, (u32)(pf_id));

	/* Set PQ sizes */       
	STORE_RT_REG(p_hwfn, QM_REG_MAXPQSIZE_2_RT_OFFSET, QM_PQ_SIZE_256B(pq_size));

	for (i = 0, pq_id = pf_id * QM_PF_QUEUE_GROUP_SIZE; i < QM_OTHER_PQS_PER_PF; i++, pq_id++) {
		/* Set PQ base address */
		STORE_RT_REG(p_hwfn, QM_REG_BASEADDROTHERPQ_RT_OFFSET + pq_id, mem_addr_4kb);

		/* Clear PQ pointer table entry */
		if (is_pf_loading)
			for (j = 0; j < 2; j++)
				STORE_RT_REG(p_hwfn, QM_REG_PTRTBLOTHER_RT_OFFSET + (pq_id * 2) + j, 0);

		mem_addr_4kb += pq_mem_4kb;
	}
}