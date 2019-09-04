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
struct wt_status_change_data {int index_status; int rename_status; int rename_score; int /*<<< orphan*/  stagemask; int /*<<< orphan*/  oid_index; int /*<<< orphan*/  oid_head; int /*<<< orphan*/  mode_index; int /*<<< orphan*/  mode_head; int /*<<< orphan*/  rename_source; } ;
struct wt_status {int committable; TYPE_2__* repo; int /*<<< orphan*/  change; } ;
struct string_list_item {struct wt_status_change_data* util; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_options {int dummy; } ;
struct diff_filepair {int status; int score; TYPE_3__* two; TYPE_1__* one; } ;
struct TYPE_6__ {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,...) ; 
#define  DIFF_STATUS_ADDED 134 
#define  DIFF_STATUS_COPIED 133 
#define  DIFF_STATUS_DELETED 132 
#define  DIFF_STATUS_MODIFIED 131 
#define  DIFF_STATUS_RENAMED 130 
#define  DIFF_STATUS_TYPE_CHANGED 129 
#define  DIFF_STATUS_UNMERGED 128 
 int MAX_SCORE ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmerged_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wt_status_change_data* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wt_status_collect_updated_cb(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	struct wt_status *s = data;
	int i;

	for (i = 0; i < q->nr; i++) {
		struct diff_filepair *p;
		struct string_list_item *it;
		struct wt_status_change_data *d;

		p = q->queue[i];
		it = string_list_insert(&s->change, p->two->path);
		d = it->util;
		if (!d) {
			d = xcalloc(1, sizeof(*d));
			it->util = d;
		}
		if (!d->index_status)
			d->index_status = p->status;
		switch (p->status) {
		case DIFF_STATUS_ADDED:
			/* Leave {mode,oid}_head zero for an add. */
			d->mode_index = p->two->mode;
			oidcpy(&d->oid_index, &p->two->oid);
			s->committable = 1;
			break;
		case DIFF_STATUS_DELETED:
			d->mode_head = p->one->mode;
			oidcpy(&d->oid_head, &p->one->oid);
			s->committable = 1;
			/* Leave {mode,oid}_index zero for a delete. */
			break;

		case DIFF_STATUS_COPIED:
		case DIFF_STATUS_RENAMED:
			if (d->rename_status)
				BUG("multiple renames on the same target? how?");
			d->rename_source = xstrdup(p->one->path);
			d->rename_score = p->score * 100 / MAX_SCORE;
			d->rename_status = p->status;
			/* fallthru */
		case DIFF_STATUS_MODIFIED:
		case DIFF_STATUS_TYPE_CHANGED:
			d->mode_head = p->one->mode;
			d->mode_index = p->two->mode;
			oidcpy(&d->oid_head, &p->one->oid);
			oidcpy(&d->oid_index, &p->two->oid);
			s->committable = 1;
			break;
		case DIFF_STATUS_UNMERGED:
			d->stagemask = unmerged_mask(s->repo->index,
						     p->two->path);
			/*
			 * Don't bother setting {mode,oid}_{head,index} since the print
			 * code will output the stage values directly and not use the
			 * values in these fields.
			 */
			break;

		default:
			BUG("unhandled diff-index status '%c'", p->status);
			break;
		}
	}
}