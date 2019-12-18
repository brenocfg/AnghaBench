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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u8 cdce925_pll_calc_p(u16 n, u16 m)
{
	u8 p;
	u16 r = n / m;

	if (r >= 16)
		return 0;
	p = 4;
	while (r > 1) {
		r >>= 1;
		--p;
	}
	return p;
}