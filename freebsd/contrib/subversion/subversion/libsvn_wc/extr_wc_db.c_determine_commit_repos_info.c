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
struct TYPE_4__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step_row (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_base_deleted ; 

__attribute__((used)) static svn_error_t *
determine_commit_repos_info(apr_int64_t *repos_id,
                            const char **repos_relpath,
                            svn_wc__db_wcroot_t *wcroot,
                            const char *local_relpath,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int op_depth;

  /* Prefer the current node's repository information.  */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (!have_row)
    return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND,
                             svn_sqlite__reset(stmt),
                             _("The node '%s' was not found."),
                             path_for_error_message(wcroot, local_relpath,
                                                    scratch_pool));

  op_depth = svn_sqlite__column_int(stmt, 0);

  if (op_depth > 0)
    {
      svn_wc__db_status_t presence = svn_sqlite__column_token(stmt, 3,
                                                              presence_map);

      if (presence == svn_wc__db_status_base_deleted)
        {
          SVN_ERR(svn_sqlite__step_row(stmt)); /* There must be a row */
          op_depth = svn_sqlite__column_int(stmt, 0);
        }
      else
        {
          const char *parent_repos_relpath;
          const char *parent_relpath;
          const char *name;

          SVN_ERR(svn_sqlite__reset(stmt));

          /* The repository relative path of an add/copy is based on its
             ancestor, not on the shadowed base layer.

             As this function is only used from the commit processing we know
             the parent directory has only a BASE row, so we can just obtain
             the information directly by recursing (once!)  */

          svn_relpath_split(&parent_relpath, &name, local_relpath,
                            scratch_pool);

          SVN_ERR(determine_commit_repos_info(repos_id, &parent_repos_relpath,
                                              wcroot, parent_relpath,
                                              scratch_pool, scratch_pool));

          *repos_relpath = svn_relpath_join(parent_repos_relpath, name,
                                            result_pool);
          return SVN_NO_ERROR;
        }
    }


  SVN_ERR_ASSERT(op_depth == 0); /* And that row must be BASE */

  SVN_ERR_ASSERT(!svn_sqlite__column_is_null(stmt, 1));
  SVN_ERR_ASSERT(!svn_sqlite__column_is_null(stmt, 2));

  *repos_id = svn_sqlite__column_int64(stmt, 1);
  *repos_relpath = svn_sqlite__column_text(stmt, 2, result_pool);

  return svn_error_trace(svn_sqlite__reset(stmt));
}