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
struct clk {scalar_t__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct clk const*) ; 

bool clk_is_match(const struct clk *p, const struct clk *q)
{
	/* trivial case: identical struct clk's or both NULL */
	if (p == q)
		return true;

	/* true if clk->core pointers match. Avoid dereferencing garbage */
	if (!IS_ERR_OR_NULL(p) && !IS_ERR_OR_NULL(q))
		if (p->core == q->core)
			return true;

	return false;
}