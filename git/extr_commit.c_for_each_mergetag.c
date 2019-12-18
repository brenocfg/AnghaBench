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
struct commit_extra_header {int /*<<< orphan*/  key; struct commit_extra_header* next; } ;
struct commit {int dummy; } ;
typedef  int (* each_mergetag_fn ) (struct commit*,struct commit_extra_header*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_extra_headers (struct commit_extra_header*) ; 
 struct commit_extra_header* read_commit_extra_headers (struct commit*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int for_each_mergetag(each_mergetag_fn fn, struct commit *commit, void *data)
{
	struct commit_extra_header *extra, *to_free;
	int res = 0;

	to_free = read_commit_extra_headers(commit, NULL);
	for (extra = to_free; !res && extra; extra = extra->next) {
		if (strcmp(extra->key, "mergetag"))
			continue; /* not a merge tag */
		res = fn(commit, extra, data);
	}
	free_commit_extra_headers(to_free);
	return res;
}