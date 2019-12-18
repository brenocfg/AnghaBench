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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__ensure_revision_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__is_packed_revprop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_fs_fs__path_rev_absolute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__reset_revprop_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switch_to_new_revprop (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_non_packed_revprop (char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_packed_revprop (char const**,char const**,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__set_revision_proplist(svn_fs_t *fs,
                                 svn_revnum_t rev,
                                 apr_hash_t *proplist,
                                 apr_pool_t *pool)
{
  svn_boolean_t is_packed;
  const char *final_path;
  const char *tmp_path;
  const char *perms_reference;
  apr_array_header_t *files_to_delete = NULL;

  SVN_ERR(svn_fs_fs__ensure_revision_exists(rev, fs, pool));

  /* this info will not change while we hold the global FS write lock */
  is_packed = svn_fs_fs__is_packed_revprop(fs, rev);

  /* Serialize the new revprop data */
  if (is_packed)
    SVN_ERR(write_packed_revprop(&final_path, &tmp_path, &files_to_delete,
                                 fs, rev, proplist, pool));
  else
    SVN_ERR(write_non_packed_revprop(&final_path, &tmp_path,
                                     fs, rev, proplist, pool));

  /* Previous cache contents is invalid now. */
  svn_fs_fs__reset_revprop_cache(fs);

  /* We use the rev file of this revision as the perms reference,
   * because when setting revprops for the first time, the revprop
   * file won't exist and therefore can't serve as its own reference.
   * (Whereas the rev file should already exist at this point.)
   */
  perms_reference = svn_fs_fs__path_rev_absolute(fs, rev, pool);

  /* Now, switch to the new revprop data. */
  SVN_ERR(switch_to_new_revprop(fs, final_path, tmp_path, perms_reference,
                                files_to_delete, pool));

  return SVN_NO_ERROR;
}