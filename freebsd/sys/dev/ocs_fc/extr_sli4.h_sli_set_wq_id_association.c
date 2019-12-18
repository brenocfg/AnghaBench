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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline void
sli_set_wq_id_association(void *entry, uint16_t q_id)
{
	uint32_t *wqe = entry;

	/*
	 * Set Word 10, bit 0 to zero
	 * Set Word 10, bits 15:1 to the WQ ID
	 */
#if BYTE_ORDER == LITTLE_ENDIAN
	wqe[10] &= ~0xffff;
	wqe[10] |= q_id << 1;
#else
#error big endian version not defined
#endif
}