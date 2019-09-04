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
struct emitted_diff_symbol {scalar_t__ s; int flags; } ;
struct diff_options {TYPE_1__* emitted_symbols; } ;
struct TYPE_2__ {int nr; struct emitted_diff_symbol* buf; } ;

/* Variables and functions */
 scalar_t__ DIFF_SYMBOL_MINUS ; 
 int DIFF_SYMBOL_MOVED_LINE ; 
 int DIFF_SYMBOL_MOVED_LINE_ALT ; 
 int DIFF_SYMBOL_MOVED_LINE_UNINTERESTING ; 
 int DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK ; 
 scalar_t__ DIFF_SYMBOL_PLUS ; 

__attribute__((used)) static void dim_moved_lines(struct diff_options *o)
{
	int n;
	for (n = 0; n < o->emitted_symbols->nr; n++) {
		struct emitted_diff_symbol *prev = (n != 0) ?
				&o->emitted_symbols->buf[n - 1] : NULL;
		struct emitted_diff_symbol *l = &o->emitted_symbols->buf[n];
		struct emitted_diff_symbol *next =
				(n < o->emitted_symbols->nr - 1) ?
				&o->emitted_symbols->buf[n + 1] : NULL;

		/* Not a plus or minus line? */
		if (l->s != DIFF_SYMBOL_PLUS && l->s != DIFF_SYMBOL_MINUS)
			continue;

		/* Not a moved line? */
		if (!(l->flags & DIFF_SYMBOL_MOVED_LINE))
			continue;

		/*
		 * If prev or next are not a plus or minus line,
		 * pretend they don't exist
		 */
		if (prev && prev->s != DIFF_SYMBOL_PLUS &&
			    prev->s != DIFF_SYMBOL_MINUS)
			prev = NULL;
		if (next && next->s != DIFF_SYMBOL_PLUS &&
			    next->s != DIFF_SYMBOL_MINUS)
			next = NULL;

		/* Inside a block? */
		if ((prev &&
		    (prev->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK) ==
		    (l->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK)) &&
		    (next &&
		    (next->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK) ==
		    (l->flags & DIFF_SYMBOL_MOVED_LINE_ZEBRA_MASK))) {
			l->flags |= DIFF_SYMBOL_MOVED_LINE_UNINTERESTING;
			continue;
		}

		/* Check if we are at an interesting bound: */
		if (prev && (prev->flags & DIFF_SYMBOL_MOVED_LINE) &&
		    (prev->flags & DIFF_SYMBOL_MOVED_LINE_ALT) !=
		       (l->flags & DIFF_SYMBOL_MOVED_LINE_ALT))
			continue;
		if (next && (next->flags & DIFF_SYMBOL_MOVED_LINE) &&
		    (next->flags & DIFF_SYMBOL_MOVED_LINE_ALT) !=
		       (l->flags & DIFF_SYMBOL_MOVED_LINE_ALT))
			continue;

		/*
		 * The boundary to prev and next are not interesting,
		 * so this line is not interesting as a whole
		 */
		l->flags |= DIFF_SYMBOL_MOVED_LINE_UNINTERESTING;
	}
}