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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_WC__HAS_WORK_QUEUE ; 
 int /*<<< orphan*/  can_be_cleaned (int*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_dummy_callback ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_wc__adm_cleanup_tmp_area (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_is_wcroot (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_cleanup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_verify (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_find_root (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_obtain (int /*<<< orphan*/ *,char const*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_release (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__internal_walk_status (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
cleanup_internal(svn_wc__db_t *db,
                 const char *dir_abspath,
                 svn_boolean_t break_locks,
                 svn_boolean_t fix_recorded_timestamps,
                 svn_boolean_t vacuum_pristines,
                 svn_cancel_func_t cancel_func,
                 void *cancel_baton,
                 apr_pool_t *scratch_pool)
{
  int wc_format;
  svn_boolean_t is_wcroot;
  const char *lock_abspath;

  /* Can we even work with this directory?  */
  SVN_ERR(can_be_cleaned(&wc_format, db, dir_abspath, scratch_pool));

  /* We cannot obtain a lock on a directory that's within a locked
     subtree, so always run cleanup from the lock owner. */
  SVN_ERR(svn_wc__db_wclock_find_root(&lock_abspath, db, dir_abspath,
                                      scratch_pool, scratch_pool));
  if (lock_abspath)
    dir_abspath = lock_abspath;
  SVN_ERR(svn_wc__db_wclock_obtain(db, dir_abspath, -1, break_locks, scratch_pool));

  /* Run our changes before the subdirectories. We may not have to recurse
     if we blow away a subdir.  */
  if (wc_format >= SVN_WC__HAS_WORK_QUEUE)
    SVN_ERR(svn_wc__wq_run(db, dir_abspath, cancel_func, cancel_baton,
                           scratch_pool));

  SVN_ERR(svn_wc__db_is_wcroot(&is_wcroot, db, dir_abspath, scratch_pool));

#ifdef SVN_DEBUG
  SVN_ERR(svn_wc__db_verify(db, dir_abspath, scratch_pool));
#endif

  /* Perform these operations if we lock the entire working copy.
     Note that we really need to check a wcroot value and not
     svn_wc__check_wcroot() as that function, will just return true
     once we start sharing databases with externals.
   */
  if (is_wcroot && vacuum_pristines)
    {
    /* Cleanup the tmp area of the admin subdir, if running the log has not
       removed it!  The logs have been run, so anything left here has no hope
       of being useful. */
      SVN_ERR(svn_wc__adm_cleanup_tmp_area(db, dir_abspath, scratch_pool));

      /* Remove unreferenced pristine texts */
      SVN_ERR(svn_wc__db_pristine_cleanup(db, dir_abspath, scratch_pool));
    }

  if (fix_recorded_timestamps)
    {
      /* Instead of implementing a separate repair step here, use the standard
         status walker's optimized implementation, which performs repairs when
         there is a lock. */
      SVN_ERR(svn_wc__internal_walk_status(db, dir_abspath, svn_depth_infinity,
                                           FALSE /* get_all */,
                                           FALSE /* no_ignore */,
                                           FALSE /* ignore_text_mods */,
                                           NULL /* ignore patterns */,
                                           status_dummy_callback, NULL,
                                           cancel_func, cancel_baton,
                                           scratch_pool));
    }

  /* All done, toss the lock */
  SVN_ERR(svn_wc__db_wclock_release(db, dir_abspath, scratch_pool));

  return SVN_NO_ERROR;
}