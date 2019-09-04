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
struct string_list_item {int /*<<< orphan*/ * util; int /*<<< orphan*/  string; } ;
struct patch {char* new_name; char* old_name; } ;
struct TYPE_2__ {int nr; struct string_list_item* items; } ;
struct apply_state {int /*<<< orphan*/  has_include; TYPE_1__ limit_by_name; scalar_t__* prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  skip_prefix (char const*,scalar_t__*,char const**) ; 
 int /*<<< orphan*/  wildmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int use_patch(struct apply_state *state, struct patch *p)
{
	const char *pathname = p->new_name ? p->new_name : p->old_name;
	int i;

	/* Paths outside are not touched regardless of "--include" */
	if (state->prefix && *state->prefix) {
		const char *rest;
		if (!skip_prefix(pathname, state->prefix, &rest) || !*rest)
			return 0;
	}

	/* See if it matches any of exclude/include rule */
	for (i = 0; i < state->limit_by_name.nr; i++) {
		struct string_list_item *it = &state->limit_by_name.items[i];
		if (!wildmatch(it->string, pathname, 0))
			return (it->util != NULL);
	}

	/*
	 * If we had any include, a path that does not match any rule is
	 * not used.  Otherwise, we saw bunch of exclude rules (or none)
	 * and such a path is used.
	 */
	return !state->has_include;
}