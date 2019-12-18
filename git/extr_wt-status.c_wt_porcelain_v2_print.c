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
struct wt_status_change_data {scalar_t__ stagemask; } ;
struct TYPE_6__ {int nr; struct string_list_item* items; } ;
struct TYPE_5__ {int nr; struct string_list_item* items; } ;
struct TYPE_4__ {int nr; struct string_list_item* items; } ;
struct wt_status {TYPE_3__ ignored; TYPE_2__ untracked; TYPE_1__ change; scalar_t__ show_branch; } ;
struct string_list_item {struct wt_status_change_data* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  wt_porcelain_v2_print_changed_entry (struct string_list_item*,struct wt_status*) ; 
 int /*<<< orphan*/  wt_porcelain_v2_print_other (struct string_list_item*,struct wt_status*,char) ; 
 int /*<<< orphan*/  wt_porcelain_v2_print_tracking (struct wt_status*) ; 
 int /*<<< orphan*/  wt_porcelain_v2_print_unmerged_entry (struct string_list_item*,struct wt_status*) ; 

__attribute__((used)) static void wt_porcelain_v2_print(struct wt_status *s)
{
	struct wt_status_change_data *d;
	struct string_list_item *it;
	int i;

	if (s->show_branch)
		wt_porcelain_v2_print_tracking(s);

	for (i = 0; i < s->change.nr; i++) {
		it = &(s->change.items[i]);
		d = it->util;
		if (!d->stagemask)
			wt_porcelain_v2_print_changed_entry(it, s);
	}

	for (i = 0; i < s->change.nr; i++) {
		it = &(s->change.items[i]);
		d = it->util;
		if (d->stagemask)
			wt_porcelain_v2_print_unmerged_entry(it, s);
	}

	for (i = 0; i < s->untracked.nr; i++) {
		it = &(s->untracked.items[i]);
		wt_porcelain_v2_print_other(it, s, '?');
	}

	for (i = 0; i < s->ignored.nr; i++) {
		it = &(s->ignored.items[i]);
		wt_porcelain_v2_print_other(it, s, '!');
	}
}