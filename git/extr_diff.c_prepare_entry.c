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
struct moved_entry {int /*<<< orphan*/ * next_line; struct emitted_diff_symbol* es; int /*<<< orphan*/  ent; } ;
struct emitted_diff_symbol {int /*<<< orphan*/  len; int /*<<< orphan*/  line; } ;
struct diff_options {unsigned int color_moved_ws_handling; TYPE_1__* emitted_symbols; } ;
struct TYPE_2__ {struct emitted_diff_symbol* buf; } ;

/* Variables and functions */
 unsigned int XDF_WHITESPACE_FLAGS ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int xdiff_hash_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct moved_entry* xmalloc (int) ; 

__attribute__((used)) static struct moved_entry *prepare_entry(struct diff_options *o,
					 int line_no)
{
	struct moved_entry *ret = xmalloc(sizeof(*ret));
	struct emitted_diff_symbol *l = &o->emitted_symbols->buf[line_no];
	unsigned flags = o->color_moved_ws_handling & XDF_WHITESPACE_FLAGS;
	unsigned int hash = xdiff_hash_string(l->line, l->len, flags);

	hashmap_entry_init(&ret->ent, hash);
	ret->es = l;
	ret->next_line = NULL;

	return ret;
}