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
struct string_list_item {int /*<<< orphan*/ * string; int /*<<< orphan*/ * util; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ has_glob_specials (char const*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/ * strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_strip_suffix (struct strbuf*,char*) ; 

void normalize_glob_ref(struct string_list_item *item, const char *prefix,
			const char *pattern)
{
	struct strbuf normalized_pattern = STRBUF_INIT;

	if (*pattern == '/')
		BUG("pattern must not start with '/'");

	if (prefix) {
		strbuf_addstr(&normalized_pattern, prefix);
	}
	else if (!starts_with(pattern, "refs/"))
		strbuf_addstr(&normalized_pattern, "refs/");
	strbuf_addstr(&normalized_pattern, pattern);
	strbuf_strip_suffix(&normalized_pattern, "/");

	item->string = strbuf_detach(&normalized_pattern, NULL);
	item->util = has_glob_specials(pattern) ? NULL : item->string;
	strbuf_release(&normalized_pattern);
}