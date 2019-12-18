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
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline unsigned
mux_to_reg(unsigned src, unsigned map)
{
	unsigned ret, bit;

	bit = (1u << 3);
	for (ret = 0; bit; ret++, bit >>= 1) {
		if (map & bit) {
			if (src-- == 0)
				return (ret);
		}
	}
	panic("mux_to_reg");
}