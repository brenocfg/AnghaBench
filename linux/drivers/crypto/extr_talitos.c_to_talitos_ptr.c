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
struct talitos_ptr {int /*<<< orphan*/  eptr; void* len; void* len1; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void to_talitos_ptr(struct talitos_ptr *ptr, dma_addr_t dma_addr,
			   unsigned int len, bool is_sec1)
{
	ptr->ptr = cpu_to_be32(lower_32_bits(dma_addr));
	if (is_sec1) {
		ptr->len1 = cpu_to_be16(len);
	} else {
		ptr->len = cpu_to_be16(len);
		ptr->eptr = upper_32_bits(dma_addr);
	}
}