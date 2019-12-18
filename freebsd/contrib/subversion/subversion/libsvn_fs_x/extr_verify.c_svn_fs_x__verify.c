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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_progress_notify_func_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_x__ensure_revision_exists (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__youngest_rev (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_metadata_consistency (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_rep_cache (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__verify(svn_fs_t *fs,
                 svn_revnum_t start,
                 svn_revnum_t end,
                 svn_fs_progress_notify_func_t notify_func,
                 void *notify_baton,
                 svn_cancel_func_t cancel_func,
                 void *cancel_baton,
                 apr_pool_t *scratch_pool)
{
  /* Input validation. */
  if (! SVN_IS_VALID_REVNUM(start))
    start = 0;
  if (! SVN_IS_VALID_REVNUM(end))
    {
      SVN_ERR(svn_fs_x__youngest_rev(&end, fs, scratch_pool));
    }

  SVN_ERR(svn_fs_x__ensure_revision_exists(start, fs, scratch_pool));
  SVN_ERR(svn_fs_x__ensure_revision_exists(end, fs, scratch_pool));

  /* log/phys index consistency.  We need to check them first to make
     sure we can access the rev / pack files in format7. */
  SVN_ERR(verify_metadata_consistency(fs, start, end,
                                      notify_func, notify_baton,
                                      cancel_func, cancel_baton,
                                      scratch_pool));

  /* rep cache consistency */
  SVN_ERR(verify_rep_cache(fs, start, end, notify_func, notify_baton,
                            cancel_func, cancel_baton, scratch_pool));

  return SVN_NO_ERROR;
}