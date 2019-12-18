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
struct sec4_sg_entry {void* bpid_offset; void* len; int /*<<< orphan*/  ptr; } ;
struct dpaa2_sg_entry {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int SEC4_SG_OFFSET_MASK ; 
 scalar_t__ caam_dpaa2 ; 
 void* cpu_to_caam32 (int) ; 
 int /*<<< orphan*/  cpu_to_caam_dma64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_to_qm_sg_one (struct dpaa2_sg_entry*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,struct sec4_sg_entry*,int,int) ; 

__attribute__((used)) static inline void dma_to_sec4_sg_one(struct sec4_sg_entry *sec4_sg_ptr,
				      dma_addr_t dma, u32 len, u16 offset)
{
	if (caam_dpaa2) {
		dma_to_qm_sg_one((struct dpaa2_sg_entry *)sec4_sg_ptr, dma, len,
				 offset);
	} else {
		sec4_sg_ptr->ptr = cpu_to_caam_dma64(dma);
		sec4_sg_ptr->len = cpu_to_caam32(len);
		sec4_sg_ptr->bpid_offset = cpu_to_caam32(offset &
							 SEC4_SG_OFFSET_MASK);
	}

	print_hex_dump_debug("sec4_sg_ptr@: ", DUMP_PREFIX_ADDRESS, 16, 4,
			     sec4_sg_ptr, sizeof(struct sec4_sg_entry), 1);
}