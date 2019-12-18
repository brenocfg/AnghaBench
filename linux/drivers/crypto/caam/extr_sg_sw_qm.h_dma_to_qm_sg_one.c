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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qm_sg_entry {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  __dma_to_qm_sg (struct qm_sg_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_sg_entry_set_len (struct qm_sg_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dma_to_qm_sg_one(struct qm_sg_entry *qm_sg_ptr,
				    dma_addr_t dma, u32 len, u16 offset)
{
	__dma_to_qm_sg(qm_sg_ptr, dma, offset);
	qm_sg_entry_set_len(qm_sg_ptr, len);
}