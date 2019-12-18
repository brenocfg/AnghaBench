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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_page_bits_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int NBBY ; 
 int /*<<< orphan*/  atomic_set_16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set_64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_set_8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
vm_page_bits_set(vm_page_t m, vm_page_bits_t *bits, vm_page_bits_t set)
{

#if PAGE_SIZE == 32768
	atomic_set_64((uint64_t *)bits, set);
#elif PAGE_SIZE == 16384
	atomic_set_32((uint32_t *)bits, set);
#elif (PAGE_SIZE == 8192) && defined(atomic_set_16)
	atomic_set_16((uint16_t *)bits, set);
#elif (PAGE_SIZE == 4096) && defined(atomic_set_8)
	atomic_set_8((uint8_t *)bits, set);
#else		/* PAGE_SIZE <= 8192 */
	uintptr_t addr;
	int shift;

	addr = (uintptr_t)bits;
	/*
	 * Use a trick to perform a 32-bit atomic on the
	 * containing aligned word, to not depend on the existence
	 * of atomic_{set, clear}_{8, 16}.
	 */
	shift = addr & (sizeof(uint32_t) - 1);
#if BYTE_ORDER == BIG_ENDIAN
	shift = (sizeof(uint32_t) - sizeof(vm_page_bits_t) - shift) * NBBY;
#else
	shift *= NBBY;
#endif
	addr &= ~(sizeof(uint32_t) - 1);
	atomic_set_32((uint32_t *)addr, set << shift);
#endif		/* PAGE_SIZE */
}