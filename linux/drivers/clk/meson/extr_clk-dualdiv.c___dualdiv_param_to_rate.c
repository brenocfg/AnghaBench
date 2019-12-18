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
struct meson_clk_dualdiv_param {int n1; unsigned long m1; unsigned long m2; int n2; int /*<<< orphan*/  dual; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int) ; 

__attribute__((used)) static unsigned long
__dualdiv_param_to_rate(unsigned long parent_rate,
			const struct meson_clk_dualdiv_param *p)
{
	if (!p->dual)
		return DIV_ROUND_CLOSEST(parent_rate, p->n1);

	return DIV_ROUND_CLOSEST(parent_rate * (p->m1 + p->m2),
				 p->n1 * p->m1 + p->n2 * p->m2);
}