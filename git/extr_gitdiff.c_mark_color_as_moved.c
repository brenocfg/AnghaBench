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
struct moved_entry {struct moved_entry* match; int /*<<< orphan*/  wsd; int /*<<< orphan*/  es; } ;
struct moved_block {struct moved_block* match; int /*<<< orphan*/  wsd; int /*<<< orphan*/  es; } ;
struct hashmap {int dummy; } ;
struct emitted_diff_symbol {int s; int /*<<< orphan*/  flags; } ;
struct diff_options {scalar_t__ color_moved; int color_moved_ws_handling; TYPE_1__* emitted_symbols; } ;
typedef  enum diff_symbol { ____Placeholder_diff_symbol } diff_symbol ;
struct TYPE_2__ {int nr; struct emitted_diff_symbol* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct moved_entry*,int,int) ; 
 scalar_t__ COLOR_MOVED_BLOCKS ; 
 scalar_t__ COLOR_MOVED_PLAIN ; 
 int COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE ; 
#define  DIFF_SYMBOL_MINUS 129 
 int /*<<< orphan*/  DIFF_SYMBOL_MOVED_LINE ; 
 int /*<<< orphan*/  DIFF_SYMBOL_MOVED_LINE_ALT ; 
#define  DIFF_SYMBOL_PLUS 128 
 scalar_t__ adjust_last_block (struct diff_options*,int,int) ; 
 scalar_t__ compute_ws_delta (struct emitted_diff_symbol*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct moved_entry*) ; 
 struct moved_entry* hashmap_get (struct hashmap*,struct moved_entry*,int /*<<< orphan*/ *) ; 
 struct moved_entry* hashmap_get_next (struct hashmap*,struct moved_entry*) ; 
 int /*<<< orphan*/  moved_block_clear (struct moved_entry*) ; 
 int /*<<< orphan*/  pmb_advance_or_null (struct diff_options*,struct moved_entry*,struct hashmap*,struct moved_entry*,int) ; 
 int /*<<< orphan*/  pmb_advance_or_null_multi_match (struct diff_options*,struct moved_entry*,struct hashmap*,struct moved_entry*,int,int) ; 
 struct moved_entry* prepare_entry (struct diff_options*,int) ; 
 int shrink_potential_moved_blocks (struct moved_entry*,int) ; 

__attribute__((used)) static void mark_color_as_moved(struct diff_options *o,
				struct hashmap *add_lines,
				struct hashmap *del_lines)
{
	struct moved_block *pmb = NULL; /* potentially moved blocks */
	int pmb_nr = 0, pmb_alloc = 0;
	int n, flipped_block = 0, block_length = 0;


	for (n = 0; n < o->emitted_symbols->nr; n++) {
		struct hashmap *hm = NULL;
		struct moved_entry *key;
		struct moved_entry *match = NULL;
		struct emitted_diff_symbol *l = &o->emitted_symbols->buf[n];
		enum diff_symbol last_symbol = 0;

		switch (l->s) {
		case DIFF_SYMBOL_PLUS:
			hm = del_lines;
			key = prepare_entry(o, n);
			match = hashmap_get(hm, key, NULL);
			free(key);
			break;
		case DIFF_SYMBOL_MINUS:
			hm = add_lines;
			key = prepare_entry(o, n);
			match = hashmap_get(hm, key, NULL);
			free(key);
			break;
		default:
			flipped_block = 0;
		}

		if (!match) {
			int i;

			adjust_last_block(o, n, block_length);
			for(i = 0; i < pmb_nr; i++)
				moved_block_clear(&pmb[i]);
			pmb_nr = 0;
			block_length = 0;
			flipped_block = 0;
			last_symbol = l->s;
			continue;
		}

		if (o->color_moved == COLOR_MOVED_PLAIN) {
			last_symbol = l->s;
			l->flags |= DIFF_SYMBOL_MOVED_LINE;
			continue;
		}

		if (o->color_moved_ws_handling &
		    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE)
			pmb_advance_or_null_multi_match(o, match, hm, pmb, pmb_nr, n);
		else
			pmb_advance_or_null(o, match, hm, pmb, pmb_nr);

		pmb_nr = shrink_potential_moved_blocks(pmb, pmb_nr);

		if (pmb_nr == 0) {
			/*
			 * The current line is the start of a new block.
			 * Setup the set of potential blocks.
			 */
			for (; match; match = hashmap_get_next(hm, match)) {
				ALLOC_GROW(pmb, pmb_nr + 1, pmb_alloc);
				if (o->color_moved_ws_handling &
				    COLOR_MOVED_WS_ALLOW_INDENTATION_CHANGE) {
					if (compute_ws_delta(l, match->es,
							     &pmb[pmb_nr].wsd))
						pmb[pmb_nr++].match = match;
				} else {
					pmb[pmb_nr].wsd = 0;
					pmb[pmb_nr++].match = match;
				}
			}

			if (adjust_last_block(o, n, block_length) &&
			    pmb_nr && last_symbol != l->s)
				flipped_block = (flipped_block + 1) % 2;
			else
				flipped_block = 0;

			block_length = 0;
		}

		if (pmb_nr) {
			block_length++;
			l->flags |= DIFF_SYMBOL_MOVED_LINE;
			if (flipped_block && o->color_moved != COLOR_MOVED_BLOCKS)
				l->flags |= DIFF_SYMBOL_MOVED_LINE_ALT;
		}
		last_symbol = l->s;
	}
	adjust_last_block(o, n, block_length);

	for(n = 0; n < pmb_nr; n++)
		moved_block_clear(&pmb[n]);
	free(pmb);
}