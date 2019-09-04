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
struct strbuf_list {int nr; int /*<<< orphan*/ * items; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int do_not_match ; 
 int format_config (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/ * key_regexp ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regexp ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_key_regexp ; 

__attribute__((used)) static int collect_config(const char *key_, const char *value_, void *cb)
{
	struct strbuf_list *values = cb;

	if (!use_key_regexp && strcmp(key_, key))
		return 0;
	if (use_key_regexp && regexec(key_regexp, key_, 0, NULL, 0))
		return 0;
	if (regexp != NULL &&
	    (do_not_match ^ !!regexec(regexp, (value_?value_:""), 0, NULL, 0)))
		return 0;

	ALLOC_GROW(values->items, values->nr + 1, values->alloc);
	strbuf_init(&values->items[values->nr], 0);

	return format_config(&values->items[values->nr++], key_, value_);
}