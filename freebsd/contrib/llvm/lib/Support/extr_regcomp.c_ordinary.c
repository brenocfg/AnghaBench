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
typedef  int /*<<< orphan*/  uch ;
struct parse {TYPE_1__* g; } ;
typedef  scalar_t__ cat_t ;
struct TYPE_2__ {int cflags; int /*<<< orphan*/  ncategories; scalar_t__* categories; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCHAR ; 
 int REG_ICASE ; 
 int /*<<< orphan*/  bothcases (struct parse*,int) ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 int othercase (int) ; 

__attribute__((used)) static void
ordinary(struct parse *p, int ch)
{
	cat_t *cap = p->g->categories;

	if ((p->g->cflags&REG_ICASE) && isalpha((uch)ch) && othercase(ch) != ch)
		bothcases(p, ch);
	else {
		EMIT(OCHAR, (uch)ch);
		if (cap[ch] == 0)
			cap[ch] = p->g->ncategories++;
	}
}