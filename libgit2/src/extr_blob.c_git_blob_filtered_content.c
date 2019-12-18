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
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_blob_filter_options ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BLOB_FILTER_CHECK_FOR_BINARY ; 
 TYPE_1__ GIT_BLOB_FILTER_OPTIONS_INIT ; 
 int git_blob_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

int git_blob_filtered_content(
	git_buf *out,
	git_blob *blob,
	const char *path,
	int check_for_binary_data)
{
	git_blob_filter_options opts = GIT_BLOB_FILTER_OPTIONS_INIT;

	if (check_for_binary_data)
		opts.flags |= GIT_BLOB_FILTER_CHECK_FOR_BINARY;
	else
		opts.flags &= ~GIT_BLOB_FILTER_CHECK_FOR_BINARY;

	return git_blob_filter(out, blob, path, &opts);
}