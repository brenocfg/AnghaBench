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
struct moved_entry {TYPE_1__* es; } ;
struct diff_options {unsigned int color_moved_ws_handling; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE ; 
 unsigned int XDF_IGNORE_WHITESPACE ; 
 unsigned int XDF_WHITESPACE_FLAGS ; 
 int /*<<< orphan*/  xdiff_compare_lines (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int moved_entry_cmp(const void *hashmap_cmp_fn_data,
			   const void *entry,
			   const void *entry_or_key,
			   const void *keydata)
{
	const struct diff_options *diffopt = hashmap_cmp_fn_data;
	const struct moved_entry *a = entry;
	const struct moved_entry *b = entry_or_key;
	unsigned flags = diffopt->color_moved_ws_handling
			 & XDF_WHITESPACE_FLAGS;

	if (diffopt->color_moved_ws_handling &
	    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
		/*
		 * As there is not specific white space config given,
		 * we'd need to check for a new block, so ignore all
		 * white space. The setup of the white space
		 * configuration for the next block is done else where
		 */
		flags |= XDF_IGNORE_WHITESPACE;

	return !xdiff_compare_lines(a->es->line, a->es->len,
				    b->es->line, b->es->len,
				    flags);
}