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
typedef  int /*<<< orphan*/  git_vector_cmp ;
struct TYPE_3__ {scalar_t__ strcomp; int /*<<< orphan*/  pathlist; int /*<<< orphan*/  entry_srch; int /*<<< orphan*/  prefixcomp; int /*<<< orphan*/  strncomp; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_IGNORE_CASE ; 
 int /*<<< orphan*/  git__prefixcmp ; 
 int /*<<< orphan*/  git__prefixcmp_icase ; 
 scalar_t__ git__strcasecmp ; 
 scalar_t__ git__strcmp ; 
 int /*<<< orphan*/  git__strncasecmp ; 
 int /*<<< orphan*/  git__strncmp ; 
 int /*<<< orphan*/  git_index_entry_isrch ; 
 int /*<<< orphan*/  git_index_entry_srch ; 
 int /*<<< orphan*/  git_vector_set_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iterator_set_ignore_case(git_iterator *iter, bool ignore_case)
{
	if (ignore_case)
		iter->flags |= GIT_ITERATOR_IGNORE_CASE;
	else
		iter->flags &= ~GIT_ITERATOR_IGNORE_CASE;

	iter->strcomp = ignore_case ? git__strcasecmp : git__strcmp;
	iter->strncomp = ignore_case ? git__strncasecmp : git__strncmp;
	iter->prefixcomp = ignore_case ? git__prefixcmp_icase : git__prefixcmp;
	iter->entry_srch = ignore_case ? git_index_entry_isrch : git_index_entry_srch;

	git_vector_set_cmp(&iter->pathlist, (git_vector_cmp)iter->strcomp);
}