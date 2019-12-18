#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_5__ {int strategy; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ checkout_data ;

/* Variables and functions */
 int GIT_CHECKOUT_ALLOW_CONFLICTS ; 
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 scalar_t__ S_ISLNK (unsigned int) ; 
 int blob_content_to_file (TYPE_1__*,struct stat*,int /*<<< orphan*/ *,char const*,char const*,unsigned int) ; 
 int blob_content_to_link (TYPE_1__*,struct stat*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 

__attribute__((used)) static int checkout_write_content(
	checkout_data *data,
	const git_oid *oid,
	const char *full_path,
	const char *hint_path,
	unsigned int mode,
	struct stat *st)
{
	int error = 0;
	git_blob *blob;

	if ((error = git_blob_lookup(&blob, data->repo, oid)) < 0)
		return error;

	if (S_ISLNK(mode))
		error = blob_content_to_link(data, st, blob, full_path);
	else
		error = blob_content_to_file(data, st, blob, full_path, hint_path, mode);

	git_blob_free(blob);

	/* if we try to create the blob and an existing directory blocks it from
	 * being written, then there must have been a typechange conflict in a
	 * parent directory - suppress the error and try to continue.
	 */
	if ((data->strategy & GIT_CHECKOUT_ALLOW_CONFLICTS) != 0 &&
		(error == GIT_ENOTFOUND || error == GIT_EEXISTS))
	{
		git_error_clear();
		error = 0;
	}

	return error;
}