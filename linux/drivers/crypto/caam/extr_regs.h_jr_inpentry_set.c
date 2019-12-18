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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int caam_ptr_sz ; 

__attribute__((used)) static inline void jr_inpentry_set(void *inpring, int hw_idx, dma_addr_t val)
{
	if (caam_ptr_sz == sizeof(u32)) {
		u32 *inpentry = inpring;

		inpentry[hw_idx] = val;
	} else {
		dma_addr_t *inpentry = inpring;

		inpentry[hw_idx] = val;
	}
}