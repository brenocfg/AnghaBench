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
typedef  scalar_t__ uint32_t ;
struct contains_stack_entry {struct commit_list* parents; struct commit* commit; } ;
struct contains_stack {int nr; struct contains_stack_entry* contains_stack; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct contains_cache {int dummy; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {scalar_t__ generation; } ;
typedef  enum contains_result { ____Placeholder_contains_result } contains_result ;

/* Variables and functions */
#define  CONTAINS_NO 130 
#define  CONTAINS_UNKNOWN 129 
#define  CONTAINS_YES 128 
 scalar_t__ GENERATION_NUMBER_INFINITY ; 
 int* contains_cache_at (struct contains_cache*,struct commit*) ; 
 int contains_test (struct commit*,struct commit_list const*,struct contains_cache*,scalar_t__) ; 
 int /*<<< orphan*/  free (struct contains_stack_entry*) ; 
 int /*<<< orphan*/  load_commit_graph_info (int /*<<< orphan*/ ,struct commit*) ; 
 int /*<<< orphan*/  push_to_contains_stack (struct commit*,struct contains_stack*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static enum contains_result contains_tag_algo(struct commit *candidate,
					      const struct commit_list *want,
					      struct contains_cache *cache)
{
	struct contains_stack contains_stack = { 0, 0, NULL };
	enum contains_result result;
	uint32_t cutoff = GENERATION_NUMBER_INFINITY;
	const struct commit_list *p;

	for (p = want; p; p = p->next) {
		struct commit *c = p->item;
		load_commit_graph_info(the_repository, c);
		if (c->generation < cutoff)
			cutoff = c->generation;
	}

	result = contains_test(candidate, want, cache, cutoff);
	if (result != CONTAINS_UNKNOWN)
		return result;

	push_to_contains_stack(candidate, &contains_stack);
	while (contains_stack.nr) {
		struct contains_stack_entry *entry = &contains_stack.contains_stack[contains_stack.nr - 1];
		struct commit *commit = entry->commit;
		struct commit_list *parents = entry->parents;

		if (!parents) {
			*contains_cache_at(cache, commit) = CONTAINS_NO;
			contains_stack.nr--;
		}
		/*
		 * If we just popped the stack, parents->item has been marked,
		 * therefore contains_test will return a meaningful yes/no.
		 */
		else switch (contains_test(parents->item, want, cache, cutoff)) {
		case CONTAINS_YES:
			*contains_cache_at(cache, commit) = CONTAINS_YES;
			contains_stack.nr--;
			break;
		case CONTAINS_NO:
			entry->parents = parents->next;
			break;
		case CONTAINS_UNKNOWN:
			push_to_contains_stack(parents->item, &contains_stack);
			break;
		}
	}
	free(contains_stack.contains_stack);
	return contains_test(candidate, want, cache, cutoff);
}