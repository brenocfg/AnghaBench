#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_9__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_progress_notify_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
struct TYPE_10__ {scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_REP_SHARING_FORMAT ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__ensure_revision_exists (scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_fs__youngest_rev (scalar_t__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_f7_metadata_consistency (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_rep_cache (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__verify(svn_fs_t *fs,
                  svn_revnum_t start,
                  svn_revnum_t end,
                  svn_fs_progress_notify_func_t notify_func,
                  void *notify_baton,
                  svn_cancel_func_t cancel_func,
                  void *cancel_baton,
                  apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  /* Input validation. */
  if (! SVN_IS_VALID_REVNUM(start))
    start = 0;
  if (! SVN_IS_VALID_REVNUM(end))
    {
      SVN_ERR(svn_fs_fs__youngest_rev(&end, fs, pool));
    }

  SVN_ERR(svn_fs_fs__ensure_revision_exists(start, fs, pool));
  SVN_ERR(svn_fs_fs__ensure_revision_exists(end, fs, pool));

  /* log/phys index consistency.  We need to check them first to make
     sure we can access the rev / pack files in format7. */
  if (svn_fs_fs__use_log_addressing(fs))
    SVN_ERR(verify_f7_metadata_consistency(fs, start, end,
                                           notify_func, notify_baton,
                                           cancel_func, cancel_baton, pool));

  /* rep cache consistency */
  if (ffd->format >= SVN_FS_FS__MIN_REP_SHARING_FORMAT)
    SVN_ERR(verify_rep_cache(fs, start, end, notify_func, notify_baton,
                             cancel_func, cancel_baton, pool));

  return SVN_NO_ERROR;
}