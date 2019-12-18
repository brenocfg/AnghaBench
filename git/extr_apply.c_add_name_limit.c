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
struct string_list_item {void* util; } ;
struct apply_state {int /*<<< orphan*/  limit_by_name; } ;

/* Variables and functions */
 struct string_list_item* string_list_append (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void add_name_limit(struct apply_state *state,
			   const char *name,
			   int exclude)
{
	struct string_list_item *it;

	it = string_list_append(&state->limit_by_name, name);
	it->util = exclude ? NULL : (void *) 1;
}