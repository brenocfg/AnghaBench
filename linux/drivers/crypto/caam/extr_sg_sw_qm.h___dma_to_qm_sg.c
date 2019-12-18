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
typedef  int u16 ;
struct qm_sg_entry {int /*<<< orphan*/  offset; scalar_t__ bpid; scalar_t__ __reserved2; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int QM_SG_OFF_MASK ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  qm_sg_entry_set64 (struct qm_sg_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __dma_to_qm_sg(struct qm_sg_entry *qm_sg_ptr, dma_addr_t dma,
				  u16 offset)
{
	qm_sg_entry_set64(qm_sg_ptr, dma);
	qm_sg_ptr->__reserved2 = 0;
	qm_sg_ptr->bpid = 0;
	qm_sg_ptr->offset = cpu_to_be16(offset & QM_SG_OFF_MASK);
}