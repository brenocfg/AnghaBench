#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  format; int /*<<< orphan*/  path; int /*<<< orphan*/  db_path; int /*<<< orphan*/  fs_type; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  scalar_t__ svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/ * svn_fs_hotcopy_notify_t ;
struct TYPE_17__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct hotcopy_ctx_t {char const* dest; void* cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  incremental; int /*<<< orphan*/  src_len; } ;
struct fs_hotcopy_notify_baton_t {void* notify_baton; scalar_t__ notify_func; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_STATUS_IS_EEXIST (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_DIR_NOT_EMPTY ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/  SVN_REPOS__FORMAT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* create_locks (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_svn_repos_t (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fs_hotcopy_notify ; 
 int /*<<< orphan*/  get_repos (TYPE_1__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hotcopy_structure ; 
 int /*<<< orphan*/  lock_db_logs_file (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_repos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_hotcopy3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fs_hotcopy_notify_baton_t*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_dir_make_sgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_walk2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hotcopy_ctx_t*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_write_version_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_hotcopy3(const char *src_path,
                   const char *dst_path,
                   svn_boolean_t clean_logs,
                   svn_boolean_t incremental,
                   svn_repos_notify_func_t notify_func,
                   void *notify_baton,
                   svn_cancel_func_t cancel_func,
                   void *cancel_baton,
                   apr_pool_t *scratch_pool)
{
  svn_fs_hotcopy_notify_t fs_notify_func;
  struct fs_hotcopy_notify_baton_t fs_notify_baton;
  struct hotcopy_ctx_t hotcopy_context;
  const char *src_abspath;
  const char *dst_abspath;
  svn_repos_t *src_repos;
  svn_repos_t *dst_repos;
  svn_error_t *err;

  SVN_ERR(svn_dirent_get_absolute(&src_abspath, src_path, scratch_pool));
  SVN_ERR(svn_dirent_get_absolute(&dst_abspath, dst_path, scratch_pool));
  if (strcmp(src_abspath, dst_abspath) == 0)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                             _("Hotcopy source and destination are equal"));

  /* Try to open original repository */
  SVN_ERR(get_repos(&src_repos, src_abspath,
                    FALSE, FALSE,
                    FALSE,    /* don't try to open the db yet. */
                    NULL,
                    scratch_pool, scratch_pool));

  /* If we are going to clean logs, then get an exclusive lock on
     db-logs.lock, to ensure that no one else will work with logs.

     If we are just copying, then get a shared lock to ensure that
     no one else will clean logs while we copying them */

  SVN_ERR(lock_db_logs_file(src_repos, clean_logs, scratch_pool));

  /* Copy the repository to a new path, with exception of
     specially handled directories */

  hotcopy_context.dest = dst_abspath;
  hotcopy_context.src_len = strlen(src_abspath);
  hotcopy_context.incremental = incremental;
  hotcopy_context.cancel_func = cancel_func;
  hotcopy_context.cancel_baton = cancel_baton;
  SVN_ERR(svn_io_dir_walk2(src_abspath,
                           0,
                           hotcopy_structure,
                           &hotcopy_context,
                           scratch_pool));

  /* Prepare dst_repos object so that we may create locks,
     so that we may open repository */

  dst_repos = create_svn_repos_t(dst_abspath, scratch_pool);
  dst_repos->fs_type = src_repos->fs_type;
  dst_repos->format = src_repos->format;

  err = create_locks(dst_repos, scratch_pool);
  if (err)
    {
      if (incremental && err->apr_err == SVN_ERR_DIR_NOT_EMPTY)
        svn_error_clear(err);
      else
        return svn_error_trace(err);
    }

  err = svn_io_dir_make_sgid(dst_repos->db_path, APR_OS_DEFAULT,
                             scratch_pool);
  if (err)
    {
      if (incremental && APR_STATUS_IS_EEXIST(err->apr_err))
        svn_error_clear(err);
      else
        return svn_error_trace(err);
    }

  /* Exclusively lock the new repository.
     No one should be accessing it at the moment */
  SVN_ERR(lock_repos(dst_repos, TRUE, FALSE, scratch_pool));

  fs_notify_func = notify_func ? fs_hotcopy_notify : NULL;
  fs_notify_baton.notify_func = notify_func;
  fs_notify_baton.notify_baton = notify_baton;

  SVN_ERR(svn_fs_hotcopy3(src_repos->db_path, dst_repos->db_path,
                          clean_logs, incremental,
                          fs_notify_func, &fs_notify_baton,
                          cancel_func, cancel_baton, scratch_pool));

  /* Destination repository is ready.  Stamp it with a format number. */
  return svn_io_write_version_file
          (svn_dirent_join(dst_repos->path, SVN_REPOS__FORMAT, scratch_pool),
           dst_repos->format, scratch_pool);
}