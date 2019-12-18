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

/* Variables and functions */
 scalar_t__ ONE_MB ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 unsigned long PROM_ERROR ; 
 scalar_t__ RAM_END ; 
 scalar_t__ _ALIGN_UP (unsigned long,scalar_t__) ; 
 scalar_t__ _end ; 
 scalar_t__ claim_base ; 
 scalar_t__ of_claim (scalar_t__,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static void *of_try_claim(unsigned long size)
{
	unsigned long addr = 0;

	if (claim_base == 0)
		claim_base = _ALIGN_UP((unsigned long)_end, ONE_MB);

	for(; claim_base < RAM_END; claim_base += ONE_MB) {
#ifdef DEBUG
		printf("    trying: 0x%08lx\n\r", claim_base);
#endif
		addr = (unsigned long) of_claim(claim_base, size, 0);
		if (addr != PROM_ERROR)
			break;
	}
	if (addr == 0)
		return NULL;
	claim_base = PAGE_ALIGN(claim_base + size);
	return (void *)addr;
}