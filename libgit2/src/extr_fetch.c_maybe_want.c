#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int local; int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_remote_head ;
typedef  scalar_t__ git_remote_autotag_option_t ;
struct TYPE_8__ {int need_pack; int /*<<< orphan*/  refs; } ;
typedef  TYPE_2__ git_remote ;
typedef  int /*<<< orphan*/  git_refspec ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 scalar_t__ GIT_REMOTE_DOWNLOAD_TAGS_ALL ; 
 scalar_t__ git_odb_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_is_valid_name (int /*<<< orphan*/ ) ; 
 scalar_t__ git_refspec_src_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_remote__matching_refspec (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int git_vector_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int maybe_want(git_remote *remote, git_remote_head *head, git_odb *odb, git_refspec *tagspec, git_remote_autotag_option_t tagopt)
{
	int match = 0;

	if (!git_reference_is_valid_name(head->name))
		return 0;

	if (tagopt == GIT_REMOTE_DOWNLOAD_TAGS_ALL) {
		/*
		 * If tagopt is --tags, always request tags
		 * in addition to the remote's refspecs
		 */
		if (git_refspec_src_matches(tagspec, head->name))
			match = 1;
	}

	if (!match && git_remote__matching_refspec(remote, head->name))
		match = 1;

	if (!match)
		return 0;

	/* If we have the object, mark it so we don't ask for it */
	if (git_odb_exists(odb, &head->oid)) {
		head->local = 1;
	}
	else
		remote->need_pack = 1;

	return git_vector_insert(&remote->refs, head);
}