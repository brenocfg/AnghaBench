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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_11__ {int /*<<< orphan*/  flush_to_disk; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_fs_x__batch_fsync_t ;
struct TYPE_12__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/  svn_fs_x__batch_fsync_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__ensure_revision_exists (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int svn_fs_x__is_packed_revprop (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* svn_fs_x__path_rev_absolute (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_revprops (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  switch_to_new_revprop (TYPE_2__*,char const*,char const*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_non_packed_revprop (char const**,char const**,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_packed_revprop (char const**,char const**,int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__set_revision_proplist(svn_fs_t *fs,
                                svn_revnum_t rev,
                                apr_hash_t *proplist,
                                apr_pool_t *scratch_pool)
{
  svn_boolean_t is_packed;
  svn_boolean_t bump_generation = FALSE;
  const char *final_path;
  const char *tmp_path;
  const char *perms_reference;
  apr_array_header_t *files_to_delete = NULL;
  svn_fs_x__batch_fsync_t *batch;
  svn_fs_x__data_t *ffd = fs->fsap_data;

  SVN_ERR(svn_fs_x__ensure_revision_exists(rev, fs, scratch_pool));

  /* Perform all fsyncs through this instance. */
  SVN_ERR(svn_fs_x__batch_fsync_create(&batch, ffd->flush_to_disk,
                                       scratch_pool));

  /* this info will not change while we hold the global FS write lock */
  is_packed = svn_fs_x__is_packed_revprop(fs, rev);

  /* Test whether revprops already exist for this revision.
   * Only then will we need to bump the revprop generation.
   * The fact that they did not yet exist is never cached. */
  if (is_packed)
    {
      bump_generation = TRUE;
    }
  else
    {
      svn_node_kind_t kind;
      SVN_ERR(svn_io_check_path(svn_fs_x__path_revprops(fs, rev,
                                                        scratch_pool),
                                &kind, scratch_pool));
      bump_generation = kind != svn_node_none;
    }

  /* Serialize the new revprop data */
  if (is_packed)
    SVN_ERR(write_packed_revprop(&final_path, &tmp_path, &files_to_delete,
                                 fs, rev, proplist, batch, scratch_pool,
                                 scratch_pool));
  else
    SVN_ERR(write_non_packed_revprop(&final_path, &tmp_path,
                                     fs, rev, proplist, batch, 
                                     scratch_pool, scratch_pool));

  /* We use the rev file of this revision as the perms reference,
   * because when setting revprops for the first time, the revprop
   * file won't exist and therefore can't serve as its own reference.
   * (Whereas the rev file should already exist at this point.)
   */
  perms_reference = svn_fs_x__path_rev_absolute(fs, rev, scratch_pool);

  /* Now, switch to the new revprop data. */
  SVN_ERR(switch_to_new_revprop(fs, final_path, tmp_path, perms_reference,
                                files_to_delete, bump_generation, batch,
                                scratch_pool));

  return SVN_NO_ERROR;
}