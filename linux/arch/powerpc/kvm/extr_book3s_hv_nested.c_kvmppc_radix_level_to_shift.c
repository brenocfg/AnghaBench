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

__attribute__((used)) static inline int kvmppc_radix_level_to_shift(int level)
{
	switch (level) {
	case 2:
		return PUD_SHIFT;
	case 1:
		return PMD_SHIFT;
	default:
		return PAGE_SHIFT;
	}
}