#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
typedef  unsigned int uint32_t ;
typedef  int off_t ;
struct TYPE_3__ {unsigned int* pt_map; unsigned int pt_map_size; unsigned int* pt_popcounts; unsigned int pt_sparse_size; int pt_sparse_off; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 unsigned int BITS_IN (unsigned int) ; 
 unsigned int MIN (unsigned int,unsigned int) ; 
 unsigned int NBBY ; 
 unsigned int POPCOUNTS_IN (unsigned int) ; 
 unsigned int POPCOUNT_BITS ; 
 unsigned int popcount_bytes (unsigned int*,unsigned int,unsigned int) ; 
 unsigned int uint8_t ; 

off_t
_kvm_pt_find(kvm_t *kd, uint64_t pa, unsigned int page_size)
{
	uint64_t *bitmap = kd->pt_map;
	uint64_t pte_bit_id = pa / page_size;
	uint64_t pte_u64 = pte_bit_id / BITS_IN(*bitmap);
	uint64_t popcount_id = pte_bit_id / POPCOUNT_BITS;
	uint64_t pte_mask = 1ULL << (pte_bit_id % BITS_IN(*bitmap));
	uint64_t bitN;
	uint32_t count;

	/* Check whether the page address requested is in the dump. */
	if (pte_bit_id >= (kd->pt_map_size * NBBY) ||
	    (bitmap[pte_u64] & pte_mask) == 0)
		return (-1);

	/*
	 * Add/sub popcounts from the bitmap until the PTE's bit is reached.
	 * For bits that are in the upper half between the calculated
	 * popcount id and the next one, use the next one and subtract to
	 * minimize the number of popcounts required.
	 */
	if ((pte_bit_id % POPCOUNT_BITS) < (POPCOUNT_BITS / 2)) {
		count = kd->pt_popcounts[popcount_id] + popcount_bytes(
		    bitmap + popcount_id * POPCOUNTS_IN(*bitmap),
		    0, pte_bit_id - popcount_id * POPCOUNT_BITS);
	} else {
		/*
		 * Counting in reverse is trickier, since we must avoid
		 * reading from bytes that are not in range, and invert.
		 */
		uint64_t pte_u64_bit_off = pte_u64 * BITS_IN(*bitmap);

		popcount_id++;
		bitN = MIN(popcount_id * POPCOUNT_BITS,
		    kd->pt_map_size * BITS_IN(uint8_t));
		count = kd->pt_popcounts[popcount_id] - popcount_bytes(
		    bitmap + pte_u64,
		    pte_bit_id - pte_u64_bit_off, bitN - pte_u64_bit_off);
	}

	/*
	 * This can only happen if the core is truncated.  Treat these
	 * entries as if they don't exist, since their backing doesn't.
	 */
	if (count >= (kd->pt_sparse_size / page_size))
		return (-1);

	return (kd->pt_sparse_off + (uint64_t)count * page_size);
}