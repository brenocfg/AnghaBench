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
typedef  int in_addr_t ;

/* Variables and functions */

__attribute__((used)) static in_addr_t
countmask(unsigned m)
{
	in_addr_t mask;

	if (m == 0) {
		mask = 0x0;
	} else {
		mask = 1 << (32 - m);
		mask--;
		mask = ~mask;
	}
	return (mask);
}