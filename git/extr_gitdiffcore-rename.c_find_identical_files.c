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
struct hashmap {int dummy; } ;
struct file_similarity {int /*<<< orphan*/  index; struct diff_filespec* filespec; } ;
struct diff_options {scalar_t__ detect_rename; int /*<<< orphan*/  repo; } ;
struct diff_filespec {scalar_t__ mode; scalar_t__ rename_used; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {struct diff_filespec* two; } ;

/* Variables and functions */
 scalar_t__ DIFF_DETECT_COPY ; 
 int /*<<< orphan*/  MAX_SCORE ; 
 int /*<<< orphan*/  S_ISREG (scalar_t__) ; 
 scalar_t__ basename_same (struct diff_filespec*,struct diff_filespec*) ; 
 int /*<<< orphan*/  hash_filespec (int /*<<< orphan*/ ,struct diff_filespec*) ; 
 struct file_similarity* hashmap_get_from_hash (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct file_similarity* hashmap_get_next (struct hashmap*,struct file_similarity*) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_rename_pair (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rename_dst ; 

__attribute__((used)) static int find_identical_files(struct hashmap *srcs,
				int dst_index,
				struct diff_options *options)
{
	int renames = 0;

	struct diff_filespec *target = rename_dst[dst_index].two;
	struct file_similarity *p, *best = NULL;
	int i = 100, best_score = -1;

	/*
	 * Find the best source match for specified destination.
	 */
	p = hashmap_get_from_hash(srcs,
				  hash_filespec(options->repo, target),
				  NULL);
	for (; p; p = hashmap_get_next(srcs, p)) {
		int score;
		struct diff_filespec *source = p->filespec;

		/* False hash collision? */
		if (!oideq(&source->oid, &target->oid))
			continue;
		/* Non-regular files? If so, the modes must match! */
		if (!S_ISREG(source->mode) || !S_ISREG(target->mode)) {
			if (source->mode != target->mode)
				continue;
		}
		/* Give higher scores to sources that haven't been used already */
		score = !source->rename_used;
		if (source->rename_used && options->detect_rename != DIFF_DETECT_COPY)
			continue;
		score += basename_same(source, target);
		if (score > best_score) {
			best = p;
			best_score = score;
			if (score == 2)
				break;
		}

		/* Too many identical alternatives? Pick one */
		if (!--i)
			break;
	}
	if (best) {
		record_rename_pair(dst_index, best->index, MAX_SCORE);
		renames++;
	}
	return renames;
}