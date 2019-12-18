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
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_del_on_close ; 
 int /*<<< orphan*/  svn_io_file_move (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_open_unique_file3 (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_dir2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_wc__adm_child (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_drop_root (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_obtain (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wclock_owns_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_copy3 (TYPE_1__*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
integrate_nested_wc_as_copy(svn_wc_context_t *wc_ctx,
                            const char *local_abspath,
                            apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  const char *moved_abspath;

  /* Drop any references to the wc that is to be rewritten */
  SVN_ERR(svn_wc__db_drop_root(db, local_abspath, scratch_pool));

  /* Move the admin dir from the wc to a temporary location: MOVED_ABSPATH */
  {
    const char *tmpdir_abspath;
    const char *moved_adm_abspath;
    const char *adm_abspath;

    SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&tmpdir_abspath, db,
                                           svn_dirent_dirname(local_abspath,
                                                              scratch_pool),
                                           scratch_pool, scratch_pool));
    SVN_ERR(svn_io_open_unique_file3(NULL, &moved_abspath, tmpdir_abspath,
                                     svn_io_file_del_on_close,
                                     scratch_pool, scratch_pool));
    SVN_ERR(svn_io_dir_make(moved_abspath, APR_OS_DEFAULT, scratch_pool));

    adm_abspath = svn_wc__adm_child(local_abspath, "", scratch_pool);
    moved_adm_abspath = svn_wc__adm_child(moved_abspath, "", scratch_pool);
    SVN_ERR(svn_io_file_move(adm_abspath, moved_adm_abspath, scratch_pool));
  }

  /* Copy entries from temporary location into the main db */
  SVN_ERR(svn_wc_copy3(wc_ctx, moved_abspath, local_abspath,
                       TRUE /* metadata_only */,
                       NULL, NULL, NULL, NULL, scratch_pool));

  /* Cleanup the temporary admin dir */
  SVN_ERR(svn_wc__db_drop_root(db, moved_abspath, scratch_pool));
  SVN_ERR(svn_io_remove_dir2(moved_abspath, FALSE, NULL, NULL,
                             scratch_pool));

  /* The subdir is now part of our parent working copy. Our caller assumes
     that we return the new node locked, so obtain a lock if we didn't
     receive the lock via our depth infinity lock */
  {
    svn_boolean_t owns_lock;

    SVN_ERR(svn_wc__db_wclock_owns_lock(&owns_lock, db, local_abspath,
                                        FALSE, scratch_pool));
    if (!owns_lock)
      SVN_ERR(svn_wc__db_wclock_obtain(db, local_abspath, 0, FALSE,
                                       scratch_pool));
  }

  return SVN_NO_ERROR;
}