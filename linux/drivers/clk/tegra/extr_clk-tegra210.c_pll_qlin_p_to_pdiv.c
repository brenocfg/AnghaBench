#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ pdiv; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int PLL_QLIN_PDIV_MAX ; 
 TYPE_1__* pll_qlin_pdiv_to_hw ; 

__attribute__((used)) static u32 pll_qlin_p_to_pdiv(u32 p, u32 *pdiv)
{
	int i;

	if (p) {
		for (i = 0; i <= PLL_QLIN_PDIV_MAX; i++) {
			if (p <= pll_qlin_pdiv_to_hw[i].pdiv) {
				if (pdiv)
					*pdiv = i;
				return pll_qlin_pdiv_to_hw[i].pdiv;
			}
		}
	}

	return -EINVAL;
}