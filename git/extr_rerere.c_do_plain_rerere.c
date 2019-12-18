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
struct string_list {int nr; TYPE_3__* items; } ;
struct rerere_id {int dummy; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {char* string; } ;
struct TYPE_5__ {struct rerere_id* util; } ;
struct TYPE_4__ {int /*<<< orphan*/  util; } ;

/* Variables and functions */
 int GIT_MAX_RAWSZ ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  do_rerere_one_path (int /*<<< orphan*/ ,TYPE_3__*,struct string_list*) ; 
 int /*<<< orphan*/  find_conflict (struct repository*,struct string_list*) ; 
 int handle_file (int /*<<< orphan*/ ,char const*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mkdir_in_gitdir (int /*<<< orphan*/ ) ; 
 struct rerere_id* new_rerere_id (unsigned char*) ; 
 int /*<<< orphan*/  remove_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rerere_path (struct rerere_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ string_list_has_string (struct string_list*,char const*) ; 
 TYPE_2__* string_list_insert (struct string_list*,char const*) ; 
 TYPE_1__* string_list_lookup (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_remove (struct string_list*,char const*,int) ; 
 int /*<<< orphan*/  update_paths (struct repository*,struct string_list*) ; 
 int write_rr (struct string_list*,int) ; 

__attribute__((used)) static int do_plain_rerere(struct repository *r,
			   struct string_list *rr, int fd)
{
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list update = STRING_LIST_INIT_DUP;
	int i;

	find_conflict(r, &conflict);

	/*
	 * MERGE_RR records paths with conflicts immediately after
	 * merge failed.  Some of the conflicted paths might have been
	 * hand resolved in the working tree since then, but the
	 * initial run would catch all and register their preimages.
	 */
	for (i = 0; i < conflict.nr; i++) {
		struct rerere_id *id;
		unsigned char hash[GIT_MAX_RAWSZ];
		const char *path = conflict.items[i].string;
		int ret;

		/*
		 * Ask handle_file() to scan and assign a
		 * conflict ID.  No need to write anything out
		 * yet.
		 */
		ret = handle_file(r->index, path, hash, NULL);
		if (ret != 0 && string_list_has_string(rr, path)) {
			remove_variant(string_list_lookup(rr, path)->util);
			string_list_remove(rr, path, 1);
		}
		if (ret < 1)
			continue;

		id = new_rerere_id(hash);
		string_list_insert(rr, path)->util = id;

		/* Ensure that the directory exists. */
		mkdir_in_gitdir(rerere_path(id, NULL));
	}

	for (i = 0; i < rr->nr; i++)
		do_rerere_one_path(r->index, &rr->items[i], &update);

	if (update.nr)
		update_paths(r, &update);

	return write_rr(rr, fd);
}