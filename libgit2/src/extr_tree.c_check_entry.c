#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  scalar_t__ git_filemode_t ;

/* Variables and functions */
 scalar_t__ GIT_FILEMODE_COMMIT ; 
 int /*<<< orphan*/  git_object__is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  otype_from_mode (scalar_t__) ; 
 int tree_error (char*,char const*) ; 
 int /*<<< orphan*/  valid_entry_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  valid_filemode (scalar_t__) ; 

__attribute__((used)) static int check_entry(git_repository *repo, const char *filename, const git_oid *id, git_filemode_t filemode)
{
	if (!valid_filemode(filemode))
		return tree_error("failed to insert entry: invalid filemode for file", filename);

	if (!valid_entry_name(repo, filename))
		return tree_error("failed to insert entry: invalid name for a tree entry", filename);

	if (git_oid_is_zero(id))
		return tree_error("failed to insert entry: invalid null OID", filename);

	if (filemode != GIT_FILEMODE_COMMIT &&
	    !git_object__is_valid(repo, id, otype_from_mode(filemode)))
		return tree_error("failed to insert entry: invalid object specified", filename);

	return 0;
}