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
typedef  int uint64_t ;

/* Variables and functions */
 int __tlb_probe (int) ; 

int cvmx_tlb_lookup(uint64_t vaddr) {
	uint64_t hi= (vaddr >> 13 ) << 13; /* We always use ASID 0 */

	return  __tlb_probe(hi);
}