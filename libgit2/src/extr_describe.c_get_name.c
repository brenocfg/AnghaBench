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
struct get_name_data {int /*<<< orphan*/  names; int /*<<< orphan*/  repo; TYPE_1__* opts; } ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_2__ {scalar_t__ describe_strategy; scalar_t__ pattern; } ;

/* Variables and functions */
 scalar_t__ GIT_DESCRIBE_ALL ; 
 int /*<<< orphan*/  GIT_REFS_DIR ; 
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 int /*<<< orphan*/  add_to_known_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int retrieve_peeled_tag_or_object_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ wildmatch (scalar_t__,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_name(const char *refname, void *payload)
{
	struct get_name_data *data;
	bool is_tag, is_annotated, all;
	git_oid peeled, sha1;
	unsigned int prio;
	int error = 0;

	data = (struct get_name_data *)payload;
	is_tag = !git__prefixcmp(refname, GIT_REFS_TAGS_DIR);
	all = data->opts->describe_strategy == GIT_DESCRIBE_ALL;

	/* Reject anything outside refs/tags/ unless --all */
	if (!all && !is_tag)
		return 0;

	/* Accept only tags that match the pattern, if given */
	if (data->opts->pattern && (!is_tag || wildmatch(data->opts->pattern,
		refname + strlen(GIT_REFS_TAGS_DIR), 0)))
				return 0;

	/* Is it annotated? */
	if ((error = retrieve_peeled_tag_or_object_oid(
		&peeled, &sha1, data->repo, refname)) < 0)
		return error;

	is_annotated = error;

	/*
	 * By default, we only use annotated tags, but with --tags
	 * we fall back to lightweight ones (even without --tags,
	 * we still remember lightweight ones, only to give hints
	 * in an error message).  --all allows any refs to be used.
	 */
	if (is_annotated)
		prio = 2;
	else if (is_tag)
		prio = 1;
	else
		prio = 0;

	add_to_known_names(data->repo, data->names,
		all ? refname + strlen(GIT_REFS_DIR) : refname + strlen(GIT_REFS_TAGS_DIR),
		&peeled, prio, &sha1);
	return 0;
}