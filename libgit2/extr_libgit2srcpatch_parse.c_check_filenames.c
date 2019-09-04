#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* delta; } ;
struct TYPE_12__ {char* old_path; char* new_path; char* header_old_path; char* header_new_path; char const* rename_old_path; char const* rename_new_path; TYPE_4__ base; int /*<<< orphan*/  new_prefix; int /*<<< orphan*/  old_prefix; } ;
typedef  TYPE_5__ git_patch_parsed ;
struct TYPE_9__ {char const* path; } ;
struct TYPE_8__ {char const* path; } ;
struct TYPE_10__ {scalar_t__ status; TYPE_2__ new_file; TYPE_1__ old_file; } ;

/* Variables and functions */
 scalar_t__ GIT_DELTA_ADDED ; 
 scalar_t__ GIT_DELTA_DELETED ; 
 scalar_t__ check_header_names (char*,char*,char*,int) ; 
 scalar_t__ check_prefix (int /*<<< orphan*/ *,size_t*,TYPE_5__*,char const*) ; 
 int git_parse_err (char*) ; 

__attribute__((used)) static int check_filenames(git_patch_parsed *patch)
{
	const char *prefixed_new, *prefixed_old;
	size_t old_prefixlen = 0, new_prefixlen = 0;
	bool added = (patch->base.delta->status == GIT_DELTA_ADDED);
	bool deleted = (patch->base.delta->status == GIT_DELTA_DELETED);

	if (patch->old_path && !patch->new_path)
		return git_parse_err("missing new path");

	if (!patch->old_path && patch->new_path)
		return git_parse_err("missing old path");

	/* Ensure (non-renamed) paths match */
	if (check_header_names(patch->header_old_path, patch->old_path, "old", added) < 0 ||
	    check_header_names(patch->header_new_path, patch->new_path, "new", deleted) < 0)
		return -1;

	prefixed_old = (!added && patch->old_path) ? patch->old_path : patch->header_old_path;
	prefixed_new = (!deleted && patch->new_path) ? patch->new_path : patch->header_new_path;

	if ((prefixed_old && check_prefix(&patch->old_prefix, &old_prefixlen, patch, prefixed_old) < 0) ||
	    (prefixed_new && check_prefix(&patch->new_prefix, &new_prefixlen, patch, prefixed_new) < 0))
		return -1;

	/* Prefer the rename filenames as they are unambiguous and unprefixed */
	if (patch->rename_old_path)
		patch->base.delta->old_file.path = patch->rename_old_path;
	else
		patch->base.delta->old_file.path = prefixed_old + old_prefixlen;

	if (patch->rename_new_path)
		patch->base.delta->new_file.path = patch->rename_new_path;
	else
		patch->base.delta->new_file.path = prefixed_new + new_prefixlen;

	if (!patch->base.delta->old_file.path &&
	    !patch->base.delta->new_file.path)
		return git_parse_err("git diff header lacks old / new paths");

	return 0;
}