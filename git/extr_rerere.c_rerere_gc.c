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
typedef  scalar_t__ timestamp_t ;
struct string_list {int nr; TYPE_1__* items; } ;
struct rerere_id {size_t variant; struct rerere_dir* collection; } ;
struct rerere_dir {size_t status_nr; scalar_t__* status; } ;
struct repository {int dummy; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 struct rerere_dir* find_rerere_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_expiry_in_days (char*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  git_path (char*,...) ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune_one (struct rerere_id*,scalar_t__,scalar_t__) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (int /*<<< orphan*/ *) ; 
 scalar_t__ setup_rerere (struct repository*,struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock ; 

void rerere_gc(struct repository *r, struct string_list *rr)
{
	struct string_list to_remove = STRING_LIST_INIT_DUP;
	DIR *dir;
	struct dirent *e;
	int i;
	timestamp_t now = time(NULL);
	timestamp_t cutoff_noresolve = now - 15 * 86400;
	timestamp_t cutoff_resolve = now - 60 * 86400;

	if (setup_rerere(r, rr, 0) < 0)
		return;

	git_config_get_expiry_in_days("gc.rerereresolved", &cutoff_resolve, now);
	git_config_get_expiry_in_days("gc.rerereunresolved", &cutoff_noresolve, now);
	git_config(git_default_config, NULL);
	dir = opendir(git_path("rr-cache"));
	if (!dir)
		die_errno(_("unable to open rr-cache directory"));
	/* Collect stale conflict IDs ... */
	while ((e = readdir(dir))) {
		struct rerere_dir *rr_dir;
		struct rerere_id id;
		int now_empty;

		if (is_dot_or_dotdot(e->d_name))
			continue;
		rr_dir = find_rerere_dir(e->d_name);
		if (!rr_dir)
			continue; /* or should we remove e->d_name? */

		now_empty = 1;
		for (id.variant = 0, id.collection = rr_dir;
		     id.variant < id.collection->status_nr;
		     id.variant++) {
			prune_one(&id, cutoff_resolve, cutoff_noresolve);
			if (id.collection->status[id.variant])
				now_empty = 0;
		}
		if (now_empty)
			string_list_append(&to_remove, e->d_name);
	}
	closedir(dir);

	/* ... and then remove the empty directories */
	for (i = 0; i < to_remove.nr; i++)
		rmdir(git_path("rr-cache/%s", to_remove.items[i].string));
	string_list_clear(&to_remove, 0);
	rollback_lock_file(&write_lock);
}