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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 unsigned int EINVAL ; 

__attribute__((used)) static uint32_t
lbc_address_mask(uint32_t size)
{
	int n = 15;

	if (size == ~0)
		return (0);

	while (n < 32) {
		if (size == (1U << n))
			break;
		n++;
	}

	if (n == 32)
		return (EINVAL);

	return (0xffff8000 << (n - 15));
}