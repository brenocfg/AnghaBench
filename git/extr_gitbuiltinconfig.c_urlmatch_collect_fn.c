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
struct urlmatch_current_candidate_value {int value_is_null; int /*<<< orphan*/  value; } ;
struct string_list_item {struct urlmatch_current_candidate_value* util; } ;
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 
 struct string_list_item* string_list_insert (struct string_list*,char const*) ; 
 struct urlmatch_current_candidate_value* xmalloc (int) ; 

__attribute__((used)) static int urlmatch_collect_fn(const char *var, const char *value, void *cb)
{
	struct string_list *values = cb;
	struct string_list_item *item = string_list_insert(values, var);
	struct urlmatch_current_candidate_value *matched = item->util;

	if (!matched) {
		matched = xmalloc(sizeof(*matched));
		strbuf_init(&matched->value, 0);
		item->util = matched;
	} else {
		strbuf_reset(&matched->value);
	}

	if (value) {
		strbuf_addstr(&matched->value, value);
		matched->value_is_null = 0;
	} else {
		matched->value_is_null = 1;
	}
	return 0;
}