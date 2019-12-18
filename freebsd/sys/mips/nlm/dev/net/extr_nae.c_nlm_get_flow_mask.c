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

int
nlm_get_flow_mask(int num_ports)
{
	const int max_bits = 5; /* upto 32 ports */
	int i;

	/* Compute the number of bits to needed to
	 * represent all the ports */
	for (i = 0; i < max_bits; i++) {
		if (num_ports <= (2 << i))
			return (i + 1);
	}
	return (max_bits);
}