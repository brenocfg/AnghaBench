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
struct string_list_item {int /*<<< orphan*/  string; int /*<<< orphan*/ * util; } ;

/* Variables and functions */
 scalar_t__ skip_prefix (char const*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  wildmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_ref_pattern(const char *refname,
			     const struct string_list_item *item)
{
	int matched = 0;
	if (item->util == NULL) {
		if (!wildmatch(item->string, refname, 0))
			matched = 1;
	} else {
		const char *rest;
		if (skip_prefix(refname, item->string, &rest) &&
		    (!*rest || *rest == '/'))
			matched = 1;
	}
	return matched;
}