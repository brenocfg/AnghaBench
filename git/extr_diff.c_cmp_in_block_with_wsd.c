#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct moved_entry {TYPE_2__* es; } ;
struct moved_block {int wsd; } ;
struct emitted_diff_symbol {int len; char* line; int indent_off; int indent_width; } ;
struct diff_options {TYPE_1__* emitted_symbols; } ;
struct TYPE_4__ {int len; char* line; int indent_off; int indent_width; scalar_t__ s; } ;
struct TYPE_3__ {struct emitted_diff_symbol* buf; } ;

/* Variables and functions */
 scalar_t__ DIFF_SYMBOL_PLUS ; 
 int INDENT_BLANKLINE ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,int) ; 

__attribute__((used)) static int cmp_in_block_with_wsd(const struct diff_options *o,
				 const struct moved_entry *cur,
				 const struct moved_entry *match,
				 struct moved_block *pmb,
				 int n)
{
	struct emitted_diff_symbol *l = &o->emitted_symbols->buf[n];
	int al = cur->es->len, bl = match->es->len, cl = l->len;
	const char *a = cur->es->line,
		   *b = match->es->line,
		   *c = l->line;
	int a_off = cur->es->indent_off,
	    a_width = cur->es->indent_width,
	    c_off = l->indent_off,
	    c_width = l->indent_width;
	int delta;

	/*
	 * We need to check if 'cur' is equal to 'match'.  As those
	 * are from the same (+/-) side, we do not need to adjust for
	 * indent changes. However these were found using fuzzy
	 * matching so we do have to check if they are equal. Here we
	 * just check the lengths. We delay calling memcmp() to check
	 * the contents until later as if the length comparison for a
	 * and c fails we can avoid the call all together.
	 */
	if (al != bl)
		return 1;

	/* If 'l' and 'cur' are both blank then they match. */
	if (a_width == INDENT_BLANKLINE && c_width == INDENT_BLANKLINE)
		return 0;

	/*
	 * The indent changes of the block are known and stored in pmb->wsd;
	 * however we need to check if the indent changes of the current line
	 * match those of the current block and that the text of 'l' and 'cur'
	 * after the indentation match.
	 */
	if (cur->es->s == DIFF_SYMBOL_PLUS)
		delta = a_width - c_width;
	else
		delta = c_width - a_width;

	/*
	 * If the previous lines of this block were all blank then set its
	 * whitespace delta.
	 */
	if (pmb->wsd == INDENT_BLANKLINE)
		pmb->wsd = delta;

	return !(delta == pmb->wsd && al - a_off == cl - c_off &&
		 !memcmp(a, b, al) && !
		 memcmp(a + a_off, c + c_off, al - a_off));
}