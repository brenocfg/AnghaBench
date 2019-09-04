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
struct string_list_item {char* string; } ;
struct show_info {char* width; struct ref_states* states; } ;
struct ref_states {int /*<<< orphan*/  stale; int /*<<< orphan*/  tracked; TYPE_1__* remote; int /*<<< orphan*/  new_refs; scalar_t__ queried; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char const*,...) ; 
 scalar_t__ string_list_has_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int show_remote_info_item(struct string_list_item *item, void *cb_data)
{
	struct show_info *info = cb_data;
	struct ref_states *states = info->states;
	const char *name = item->string;

	if (states->queried) {
		const char *fmt = "%s";
		const char *arg = "";
		if (string_list_has_string(&states->new_refs, name)) {
			fmt = _(" new (next fetch will store in remotes/%s)");
			arg = states->remote->name;
		} else if (string_list_has_string(&states->tracked, name))
			arg = _(" tracked");
		else if (string_list_has_string(&states->stale, name))
			arg = _(" stale (use 'git remote prune' to remove)");
		else
			arg = _(" ???");
		printf("    %-*s", info->width, name);
		printf(fmt, arg);
		printf("\n");
	} else
		printf("    %s\n", name);

	return 0;
}