#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  deltas; int /*<<< orphan*/  entrycomp; int /*<<< orphan*/  pfxcomp; int /*<<< orphan*/  strncomp; int /*<<< orphan*/  strcomp; TYPE_1__ opts; } ;
typedef  TYPE_2__ git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_IGNORE_CASE ; 
 int /*<<< orphan*/  git__prefixcmp ; 
 int /*<<< orphan*/  git__prefixcmp_icase ; 
 int /*<<< orphan*/  git__strcasecmp ; 
 int /*<<< orphan*/  git__strcmp ; 
 int /*<<< orphan*/  git__strncasecmp ; 
 int /*<<< orphan*/  git__strncmp ; 
 int /*<<< orphan*/  git_diff__entry_cmp ; 
 int /*<<< orphan*/  git_diff__entry_icmp ; 
 int /*<<< orphan*/  git_diff_delta__casecmp ; 
 int /*<<< orphan*/  git_diff_delta__cmp ; 
 int /*<<< orphan*/  git_vector_set_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_sort (int /*<<< orphan*/ *) ; 

void git_diff__set_ignore_case(git_diff *diff, bool ignore_case)
{
	if (!ignore_case) {
		diff->opts.flags &= ~GIT_DIFF_IGNORE_CASE;

		diff->strcomp    = git__strcmp;
		diff->strncomp   = git__strncmp;
		diff->pfxcomp    = git__prefixcmp;
		diff->entrycomp  = git_diff__entry_cmp;

		git_vector_set_cmp(&diff->deltas, git_diff_delta__cmp);
	} else {
		diff->opts.flags |= GIT_DIFF_IGNORE_CASE;

		diff->strcomp    = git__strcasecmp;
		diff->strncomp   = git__strncasecmp;
		diff->pfxcomp    = git__prefixcmp_icase;
		diff->entrycomp  = git_diff__entry_icmp;

		git_vector_set_cmp(&diff->deltas, git_diff_delta__casecmp);
	}

	git_vector_sort(&diff->deltas);
}