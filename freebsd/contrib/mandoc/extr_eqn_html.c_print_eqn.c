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
struct tag {int dummy; } ;
struct html {int /*<<< orphan*/  flags; } ;
struct eqn_box {int /*<<< orphan*/ * first; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTML_NONOSPACE ; 
 int /*<<< orphan*/  TAG_MATH ; 
 int /*<<< orphan*/  eqn_box (struct html*,struct eqn_box const*) ; 
 struct tag* print_otag (struct html*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  print_tagq (struct html*,struct tag*) ; 

void
print_eqn(struct html *p, const struct eqn_box *bp)
{
	struct tag	*t;

	if (bp->first == NULL)
		return;

	t = print_otag(p, TAG_MATH, "c", "eqn");

	p->flags |= HTML_NONOSPACE;
	eqn_box(p, bp);
	p->flags &= ~HTML_NONOSPACE;

	print_tagq(p, t);
}