#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {scalar_t__ string; struct push_info* util; } ;
struct TYPE_3__ {int nr; struct refspec_item* items; } ;
struct remote {TYPE_1__ push; scalar_t__ mirror; } ;
struct refspec_item {scalar_t__ dst; int /*<<< orphan*/  force; int /*<<< orphan*/  src; scalar_t__ matching; } ;
struct TYPE_4__ {int strdup_strings; } ;
struct ref_states {TYPE_2__ push; struct remote* remote; } ;
struct push_info {void* dest; void* status; int /*<<< orphan*/  forced; } ;

/* Variables and functions */
 void* PUSH_STATUS_NOTQUERIED ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct string_list_item* string_list_append (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 void* xcalloc (int,int) ; 
 void* xstrdup (scalar_t__) ; 

__attribute__((used)) static int get_push_ref_states_noquery(struct ref_states *states)
{
	int i;
	struct remote *remote = states->remote;
	struct string_list_item *item;
	struct push_info *info;

	if (remote->mirror)
		return 0;

	states->push.strdup_strings = 1;
	if (!remote->push.nr) {
		item = string_list_append(&states->push, _("(matching)"));
		info = item->util = xcalloc(1, sizeof(struct push_info));
		info->status = PUSH_STATUS_NOTQUERIED;
		info->dest = xstrdup(item->string);
	}
	for (i = 0; i < remote->push.nr; i++) {
		const struct refspec_item *spec = &remote->push.items[i];
		if (spec->matching)
			item = string_list_append(&states->push, _("(matching)"));
		else if (strlen(spec->src))
			item = string_list_append(&states->push, spec->src);
		else
			item = string_list_append(&states->push, _("(delete)"));

		info = item->util = xcalloc(1, sizeof(struct push_info));
		info->forced = spec->force;
		info->status = PUSH_STATUS_NOTQUERIED;
		info->dest = xstrdup(spec->dst ? spec->dst : item->string);
	}
	return 0;
}