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
 int PAGE_SHIFT ; 
 int PMD_SHIFT ; 
 int PUD_SHIFT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline int kvmppc_radix_shift_to_level(int shift)
{
	if (shift == PUD_SHIFT)
		return 2;
	if (shift == PMD_SHIFT)
		return 1;
	if (shift == PAGE_SHIFT)
		return 0;
	WARN_ON_ONCE(1);
	return 0;
}