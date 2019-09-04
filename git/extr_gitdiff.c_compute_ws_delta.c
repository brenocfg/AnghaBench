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
struct emitted_diff_symbol {int len; int indent_off; int indent_width; scalar_t__ s; scalar_t__ line; } ;

/* Variables and functions */
 scalar_t__ DIFF_SYMBOL_PLUS ; 
 int INDENT_BLANKLINE ; 
 scalar_t__ memcmp (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int compute_ws_delta(const struct emitted_diff_symbol *a,
			    const struct emitted_diff_symbol *b,
			    int *out)
{
	int a_len = a->len,
	    b_len = b->len,
	    a_off = a->indent_off,
	    a_width = a->indent_width,
	    b_off = b->indent_off,
	    b_width = b->indent_width;
	int delta;

	if (a_width == INDENT_BLANKLINE && b_width == INDENT_BLANKLINE) {
		*out = INDENT_BLANKLINE;
		return 1;
	}

	if (a->s == DIFF_SYMBOL_PLUS)
		delta = a_width - b_width;
	else
		delta = b_width - a_width;

	if (a_len - a_off != b_len - b_off ||
	    memcmp(a->line + a_off, b->line + b_off, a_len - a_off))
		return 0;

	*out = delta;

	return 1;
}