#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_EMPTY ; 
 int /*<<< orphan*/  STMT_SELECT_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  STMT_UPDATE_ACTUAL_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_skel__parse (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 void* svn_sqlite__column_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_resolve (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_op_mark_resolved_internal(svn_wc__db_wcroot_t *wcroot,
                                     const char *local_relpath,
                                     svn_wc__db_t *db,
                                     svn_boolean_t resolved_text,
                                     svn_boolean_t resolved_props,
                                     svn_boolean_t resolved_tree,
                                     const svn_skel_t *work_items,
                                     apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  int total_affected_rows = 0;
  svn_boolean_t resolved_all;
  apr_size_t conflict_len;
  const void *conflict_data;
  svn_skel_t *conflicts;

  /* Check if we have a conflict in ACTUAL */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_ACTUAL_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (! have_row)
    {
      SVN_ERR(svn_sqlite__reset(stmt));

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_NODE_INFO));

      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      SVN_ERR(svn_sqlite__reset(stmt));

      if (have_row)
        return SVN_NO_ERROR;

      return svn_error_createf(SVN_ERR_WC_PATH_NOT_FOUND, NULL,
                               _("The node '%s' was not found."),
                                   path_for_error_message(wcroot,
                                                          local_relpath,
                                                          scratch_pool));
    }

  conflict_data = svn_sqlite__column_blob(stmt, 2, &conflict_len,
                                          scratch_pool);
  SVN_ERR(svn_sqlite__reset(stmt));
  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));

  if (!conflict_data)
    return SVN_NO_ERROR;

  conflicts = svn_skel__parse(conflict_data, conflict_len, scratch_pool);
  

  SVN_ERR(svn_wc__conflict_skel_resolve(&resolved_all, conflicts,
                                        db, wcroot->abspath,
                                        resolved_text,
                                        resolved_props ? "" : NULL,
                                        resolved_tree,
                                        scratch_pool, scratch_pool));

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_UPDATE_ACTUAL_CONFLICT));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

  if (! resolved_all)
    {
      svn_stringbuf_t *sb = svn_skel__unparse(conflicts, scratch_pool);

      SVN_ERR(svn_sqlite__bind_blob(stmt, 3, sb->data, sb->len));
    }

  SVN_ERR(svn_sqlite__update(&total_affected_rows, stmt));

  /* Now, remove the actual node if it doesn't have any more useful
     information.  We only need to do this if we've remove data ourselves. */
  if (total_affected_rows > 0)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_ACTUAL_EMPTY));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  return SVN_NO_ERROR;
}