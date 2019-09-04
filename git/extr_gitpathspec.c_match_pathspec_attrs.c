#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pathspec_item {int attr_match_nr; TYPE_2__* attr_match; TYPE_3__* attr_check; } ;
struct index_state {int dummy; } ;
typedef  enum attr_match_mode { ____Placeholder_attr_match_mode } attr_match_mode ;
struct TYPE_6__ {TYPE_1__* items; } ;
struct TYPE_5__ {int match_mode; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {char* value; } ;

/* Variables and functions */
 scalar_t__ ATTR_FALSE (char const*) ; 
 scalar_t__ ATTR_TRUE (char const*) ; 
 scalar_t__ ATTR_UNSET (char const*) ; 
 int MATCH_SET ; 
 int MATCH_UNSET ; 
 int MATCH_UNSPECIFIED ; 
 int MATCH_VALUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_check_attr (struct index_state const*,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* xmemdupz (char const*,int) ; 

int match_pathspec_attrs(const struct index_state *istate,
			 const char *name, int namelen,
			 const struct pathspec_item *item)
{
	int i;
	char *to_free = NULL;

	if (name[namelen])
		name = to_free = xmemdupz(name, namelen);

	git_check_attr(istate, name, item->attr_check);

	free(to_free);

	for (i = 0; i < item->attr_match_nr; i++) {
		const char *value;
		int matched;
		enum attr_match_mode match_mode;

		value = item->attr_check->items[i].value;
		match_mode = item->attr_match[i].match_mode;

		if (ATTR_TRUE(value))
			matched = (match_mode == MATCH_SET);
		else if (ATTR_FALSE(value))
			matched = (match_mode == MATCH_UNSET);
		else if (ATTR_UNSET(value))
			matched = (match_mode == MATCH_UNSPECIFIED);
		else
			matched = (match_mode == MATCH_VALUE &&
				   !strcmp(item->attr_match[i].value, value));
		if (!matched)
			return 0;
	}

	return 1;
}