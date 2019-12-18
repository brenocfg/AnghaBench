#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_filter_options ;
typedef  int /*<<< orphan*/  git_filter_mode_t ;
typedef  int /*<<< orphan*/  git_filter_list ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 TYPE_1__ GIT_FILTER_OPTIONS_INIT ; 
 int git_filter_list__load_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

int git_filter_list_load(
	git_filter_list **filters,
	git_repository *repo,
	git_blob *blob, /* can be NULL */
	const char *path,
	git_filter_mode_t mode,
	uint32_t flags)
{
	git_filter_options filter_opts = GIT_FILTER_OPTIONS_INIT;

	filter_opts.flags = flags;

	return git_filter_list__load_ext(
		filters, repo, blob, path, mode, &filter_opts);
}