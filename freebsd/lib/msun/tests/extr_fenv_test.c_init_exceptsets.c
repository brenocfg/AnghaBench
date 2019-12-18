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
 int NEXCEPTS ; 
 unsigned int* std_except_sets ; 
 unsigned int* std_excepts ; 

__attribute__((used)) static void
init_exceptsets(void)
{
	unsigned i, j, sr;

	for (i = 0; i < 1 << NEXCEPTS; i++) {
		for (sr = i, j = 0; sr != 0; sr >>= 1, j++)
			std_except_sets[i] |= std_excepts[j] & ((~sr & 1) - 1);
	}
}