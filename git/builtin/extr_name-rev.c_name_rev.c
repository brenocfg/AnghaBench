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
typedef  int /*<<< orphan*/  timestamp_t ;
struct rev_name {char const* tip_name; int generation; int distance; int from_tag; int /*<<< orphan*/  taggerdate; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {scalar_t__ date; struct commit_list* parents; } ;
typedef  int /*<<< orphan*/  rev_name ;

/* Variables and functions */
 int MERGE_TRAVERSAL_WEIGHT ; 
 scalar_t__ cutoff ; 
 int /*<<< orphan*/  die (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct rev_name* get_commit_rev_name (struct commit*) ; 
 scalar_t__ is_better_name (struct rev_name*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  parse_commit (struct commit*) ; 
 int /*<<< orphan*/  set_commit_rev_name (struct commit*,struct rev_name*) ; 
 int /*<<< orphan*/  strip_suffix (char const*,char*,size_t*) ; 
 struct rev_name* xmalloc (int) ; 
 char* xstrfmt (char*,...) ; 

__attribute__((used)) static void name_rev(struct commit *commit,
		const char *tip_name, timestamp_t taggerdate,
		int generation, int distance, int from_tag,
		int deref)
{
	struct rev_name *name = get_commit_rev_name(commit);
	struct commit_list *parents;
	int parent_number = 1;
	char *to_free = NULL;

	parse_commit(commit);

	if (commit->date < cutoff)
		return;

	if (deref) {
		tip_name = to_free = xstrfmt("%s^0", tip_name);

		if (generation)
			die("generation: %d, but deref?", generation);
	}

	if (name == NULL) {
		name = xmalloc(sizeof(rev_name));
		set_commit_rev_name(commit, name);
		goto copy_data;
	} else if (is_better_name(name, taggerdate, distance, from_tag)) {
copy_data:
		name->tip_name = tip_name;
		name->taggerdate = taggerdate;
		name->generation = generation;
		name->distance = distance;
		name->from_tag = from_tag;
	} else {
		free(to_free);
		return;
	}

	for (parents = commit->parents;
			parents;
			parents = parents->next, parent_number++) {
		if (parent_number > 1) {
			size_t len;
			char *new_name;

			strip_suffix(tip_name, "^0", &len);
			if (generation > 0)
				new_name = xstrfmt("%.*s~%d^%d", (int)len, tip_name,
						   generation, parent_number);
			else
				new_name = xstrfmt("%.*s^%d", (int)len, tip_name,
						   parent_number);

			name_rev(parents->item, new_name, taggerdate, 0,
				 distance + MERGE_TRAVERSAL_WEIGHT,
				 from_tag, 0);
		} else {
			name_rev(parents->item, tip_name, taggerdate,
				 generation + 1, distance + 1,
				 from_tag, 0);
		}
	}
}