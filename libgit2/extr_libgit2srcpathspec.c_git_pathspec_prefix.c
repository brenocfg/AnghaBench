#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_strarray ;
struct TYPE_12__ {char* ptr; scalar_t__ size; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 scalar_t__ git__iswildcard (char const) ; 
 char* git_buf_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_text_common_prefix (TYPE_2__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_buf_text_unescape (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_2__*,int) ; 

char *git_pathspec_prefix(const git_strarray *pathspec)
{
	git_buf prefix = GIT_BUF_INIT;
	const char *scan;

	if (!pathspec || !pathspec->count ||
		git_buf_text_common_prefix(&prefix, pathspec) < 0)
		return NULL;

	/* diff prefix will only be leading non-wildcards */
	for (scan = prefix.ptr; *scan; ++scan) {
		if (git__iswildcard(*scan) &&
			(scan == prefix.ptr || (*(scan - 1) != '\\')))
			break;
	}
	git_buf_truncate(&prefix, scan - prefix.ptr);

	if (prefix.size <= 0) {
		git_buf_dispose(&prefix);
		return NULL;
	}

	git_buf_text_unescape(&prefix);

	return git_buf_detach(&prefix);
}