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
struct tree_desc {scalar_t__ size; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (unsigned short) ; 
 void* fill_tree_desc_strict (struct tree_desc*,struct object_id const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int score_trees (struct object_id const*,struct object_id const*) ; 
 struct object_id* tree_entry_extract (struct tree_desc*,char const**,unsigned short*) ; 
 int /*<<< orphan*/  update_tree_entry (struct tree_desc*) ; 
 char* xstrfmt (char*,char const*,char const*) ; 

__attribute__((used)) static void match_trees(const struct object_id *hash1,
			const struct object_id *hash2,
			int *best_score,
			char **best_match,
			const char *base,
			int recurse_limit)
{
	struct tree_desc one;
	void *one_buf = fill_tree_desc_strict(&one, hash1);

	while (one.size) {
		const char *path;
		const struct object_id *elem;
		unsigned short mode;
		int score;

		elem = tree_entry_extract(&one, &path, &mode);
		if (!S_ISDIR(mode))
			goto next;
		score = score_trees(elem, hash2);
		if (*best_score < score) {
			free(*best_match);
			*best_match = xstrfmt("%s%s", base, path);
			*best_score = score;
		}
		if (recurse_limit) {
			char *newbase = xstrfmt("%s%s/", base, path);
			match_trees(elem, hash2, best_score, best_match,
				    newbase, recurse_limit - 1);
			free(newbase);
		}

	next:
		update_tree_entry(&one);
	}
	free(one_buf);
}