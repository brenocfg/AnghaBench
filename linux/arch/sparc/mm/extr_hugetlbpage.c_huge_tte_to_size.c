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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long HPAGE_SIZE ; 
 unsigned long REAL_HPAGE_SIZE ; 
 unsigned long huge_tte_to_shift (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long huge_tte_to_size(pte_t pte)
{
	unsigned long size = 1UL << huge_tte_to_shift(pte);

	if (size == REAL_HPAGE_SIZE)
		size = HPAGE_SIZE;
	return size;
}