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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ffz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int next_index(u32 *counter)
{
	int i, res = 0;

	for (i = 0; i < 4; i++) {
		if (counter[i] + 1 != 0)
			return res + ffz(counter[i]++);

		counter[i] = 0;
		res += 32;
	}

	/*
	 * If we get here, then x == 128 and we are incrementing the counter
	 * from all ones to all zeros. This means we must return index 127, i.e.
	 * the one corresponding to key2*{ 1,...,1 }.
	 */
	return 127;
}