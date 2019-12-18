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
struct wt_status_change_data {int worktree_status; int new_submodule_commits; int rename_status; int rename_score; int /*<<< orphan*/  oid_index; int /*<<< orphan*/  mode_worktree; int /*<<< orphan*/  mode_index; int /*<<< orphan*/  rename_source; int /*<<< orphan*/  dirty_submodule; } ;
struct wt_status {int workdir_dirty; scalar_t__ status_format; int /*<<< orphan*/  change; } ;
struct string_list_item {struct wt_status_change_data* util; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_options {int dummy; } ;
struct diff_filepair {int status; int score; TYPE_2__* one; TYPE_1__* two; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  dirty_submodule; int /*<<< orphan*/  path; } ;

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
 scalar_t__ STATUS_FORMAT_SHORT ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int short_submodule_status (struct wt_status_change_data*) ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct wt_status_change_data* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wt_status_collect_changed_cb(struct diff_queue_struct *q,
					 struct diff_options *options,
					 void *data)
{
	struct wt_status *s = data;
	int i;

	if (!q->nr)
		return;
	s->workdir_dirty = 1;
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
		if (!d->worktree_status)
			d->worktree_status = p->status;
		if (S_ISGITLINK(p->two->mode)) {
			d->dirty_submodule = p->two->dirty_submodule;
			d->new_submodule_commits = !oideq(&p->one->oid,
							  &p->two->oid);
			if (s->status_format == STATUS_FORMAT_SHORT)
				d->worktree_status = short_submodule_status(d);
		}

		switch (p->status) {
		case DIFF_STATUS_ADDED:
			d->mode_worktree = p->two->mode;
			break;

		case DIFF_STATUS_DELETED:
			d->mode_index = p->one->mode;
			oidcpy(&d->oid_index, &p->one->oid);
			/* mode_worktree is zero for a delete. */
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
		case DIFF_STATUS_UNMERGED:
			d->mode_index = p->one->mode;
			d->mode_worktree = p->two->mode;
			oidcpy(&d->oid_index, &p->one->oid);
			break;

		default:
			BUG("unhandled diff-files status '%c'", p->status);
			break;
		}

	}
}