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
struct TYPE_5__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  void* svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  void* svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_EXTERNAL_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  presence_map ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_ancestor (int /*<<< orphan*/ ,char const*) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_skip_ancestor (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_revnum (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 void* svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_fetch_repos_info (char const**,char const**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_external_read(svn_wc__db_status_t *status,
                         svn_node_kind_t *kind,
                         const char **definining_abspath,
                         const char **repos_root_url,
                         const char **repos_uuid,
                         const char **recorded_repos_relpath,
                         svn_revnum_t *recorded_peg_revision,
                         svn_revnum_t *recorded_revision,
                         svn_wc__db_t *db,
                         const char *local_abspath,
                         const char *wri_abspath,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_info;
  svn_error_t *err = NULL;
  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  if (! wri_abspath)
    wri_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_ERR_ASSERT(svn_dirent_is_ancestor(wcroot->abspath, local_abspath));

  local_relpath = svn_dirent_skip_ancestor(wcroot->abspath, local_abspath);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_EXTERNAL_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_info, stmt));

  if (have_info)
    {
      if (status)
        *status = svn_sqlite__column_token(stmt, 0, presence_map);

      if (kind)
        *kind = svn_sqlite__column_token(stmt, 1, kind_map);

      if (definining_abspath)
        {
          const char *record_relpath = svn_sqlite__column_text(stmt, 2, NULL);

          *definining_abspath = svn_dirent_join(wcroot->abspath,
                                                record_relpath, result_pool);
        }

      if (repos_root_url || repos_uuid)
        {
          apr_int64_t repos_id;

          repos_id = svn_sqlite__column_int64(stmt, 3);

          err = svn_error_compose_create(
                        err,
                        svn_wc__db_fetch_repos_info(repos_root_url, repos_uuid,
                                                    wcroot, repos_id,
                                                    result_pool));
        }

      if (recorded_repos_relpath)
        *recorded_repos_relpath = svn_sqlite__column_text(stmt, 4,
                                                          result_pool);

      if (recorded_peg_revision)
        *recorded_peg_revision = svn_sqlite__column_revnum(stmt, 5);

      if (recorded_revision)
        *recorded_revision = svn_sqlite__column_revnum(stmt, 6);
    }
  else
    {
      err = svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                              _("The node '%s' is not an external."),
                              svn_dirent_local_style(local_abspath,
                                                     scratch_pool));
    }

  return svn_error_trace(
                svn_error_compose_create(err, svn_sqlite__reset(stmt)));
}