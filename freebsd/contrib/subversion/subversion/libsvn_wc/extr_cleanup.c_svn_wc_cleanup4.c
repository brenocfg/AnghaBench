#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_notify_func2_t ;
struct TYPE_3__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  cleanup_internal (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_wc__db_base_clear_dav_cache_recursive (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_drop_root (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_vacuum (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_cleanup4(svn_wc_context_t *wc_ctx,
                const char *local_abspath,
                svn_boolean_t break_locks,
                svn_boolean_t fix_recorded_timestamps,
                svn_boolean_t clear_dav_cache,
                svn_boolean_t vacuum_pristines,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                svn_wc_notify_func2_t notify_func,
                void *notify_baton,
                apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(wc_ctx != NULL);

  if (break_locks)
    {
      /* We'll handle everything manually.  */

      /* Close the existing database (if any) to avoid problems with
         exclusive database usage */
      SVN_ERR(svn_wc__db_drop_root(wc_ctx->db, local_abspath,
                                   scratch_pool));

      SVN_ERR(svn_wc__db_open(&db,
                              NULL /* ### config */, FALSE, FALSE,
                              scratch_pool, scratch_pool));
    }
  else
    db = wc_ctx->db;

  SVN_ERR(cleanup_internal(db, local_abspath,
                           break_locks,
                           fix_recorded_timestamps,
                           vacuum_pristines,
                           cancel_func, cancel_baton,
                           scratch_pool));

  /* The DAV cache suffers from flakiness from time to time, and the
     pre-1.7 prescribed workarounds aren't as user-friendly in WC-NG. */
  if (clear_dav_cache)
    SVN_ERR(svn_wc__db_base_clear_dav_cache_recursive(db, local_abspath,
                                                      scratch_pool));

  if (vacuum_pristines)
    SVN_ERR(svn_wc__db_vacuum(db, local_abspath, scratch_pool));

  /* We're done with this DB, so proactively close it.  */
  if (break_locks)
    SVN_ERR(svn_wc__db_close(db));

  return SVN_NO_ERROR;
}