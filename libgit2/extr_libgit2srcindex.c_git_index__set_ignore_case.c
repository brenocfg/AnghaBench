#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ignore_case; int /*<<< orphan*/  reuc; int /*<<< orphan*/  entries; int /*<<< orphan*/  reuc_search; int /*<<< orphan*/  entries_search_path; int /*<<< orphan*/  entries_search; int /*<<< orphan*/  entries_cmp_path; } ;
typedef  TYPE_1__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  git__strcasecmp_cb ; 
 int /*<<< orphan*/  git__strcmp_cb ; 
 int /*<<< orphan*/  git_index_entry_cmp ; 
 int /*<<< orphan*/  git_index_entry_icmp ; 
 int /*<<< orphan*/  git_index_entry_isrch ; 
 int /*<<< orphan*/  git_index_entry_srch ; 
 int /*<<< orphan*/  git_vector_set_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_entry_isrch_path ; 
 int /*<<< orphan*/  index_entry_srch_path ; 
 int /*<<< orphan*/  reuc_cmp ; 
 int /*<<< orphan*/  reuc_icmp ; 
 int /*<<< orphan*/  reuc_isrch ; 
 int /*<<< orphan*/  reuc_srch ; 

void git_index__set_ignore_case(git_index *index, bool ignore_case)
{
	index->ignore_case = ignore_case;

	if (ignore_case) {
		index->entries_cmp_path    = git__strcasecmp_cb;
		index->entries_search      = git_index_entry_isrch;
		index->entries_search_path = index_entry_isrch_path;
		index->reuc_search         = reuc_isrch;
	} else {
		index->entries_cmp_path    = git__strcmp_cb;
		index->entries_search      = git_index_entry_srch;
		index->entries_search_path = index_entry_srch_path;
		index->reuc_search         = reuc_srch;
	}

	git_vector_set_cmp(&index->entries,
		ignore_case ? git_index_entry_icmp : git_index_entry_cmp);
	git_vector_sort(&index->entries);

	git_vector_set_cmp(&index->reuc, ignore_case ? reuc_icmp : reuc_cmp);
	git_vector_sort(&index->reuc);
}