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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 unsigned long mult_frac (unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long cdce925_pll_calculate_rate(unsigned long parent_rate,
	u16 n, u16 m)
{
	if ((!m || !n) || (m == n))
		return parent_rate; /* In bypass mode runs at same frequency */
	return mult_frac(parent_rate, (unsigned long)n, (unsigned long)m);
}