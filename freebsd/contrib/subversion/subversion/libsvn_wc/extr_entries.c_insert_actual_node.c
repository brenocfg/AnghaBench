#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ tree_conflict_data; int /*<<< orphan*/  prop_reject; int /*<<< orphan*/  conflict_new; int /*<<< orphan*/  conflict_working; int /*<<< orphan*/  conflict_old; int /*<<< orphan*/  local_relpath; int /*<<< orphan*/  changelist; int /*<<< orphan*/  properties; int /*<<< orphan*/  parent_relpath; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_2__ db_actual_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INSERT_ACTUAL_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bind_properties (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__upgrade_conflict_skel_from_raw (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
insert_actual_node(svn_sqlite__db_t *sdb,
                   svn_wc__db_t *db,
                   const char *wri_abspath,
                   const db_actual_node_t *actual_node,
                   apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_skel_t *conflict_data = NULL;

  SVN_ERR(svn_sqlite__get_statement(&stmt, sdb, STMT_INSERT_ACTUAL_NODE));

  SVN_ERR(svn_sqlite__bind_int64(stmt, 1, actual_node->wc_id));
  SVN_ERR(svn_sqlite__bind_text(stmt, 2, actual_node->local_relpath));
  SVN_ERR(svn_sqlite__bind_text(stmt, 3, actual_node->parent_relpath));

  if (actual_node->properties)
    SVN_ERR(svn_sqlite__bind_properties(stmt, 4, actual_node->properties,
                                        scratch_pool));

  if (actual_node->changelist)
    SVN_ERR(svn_sqlite__bind_text(stmt, 5, actual_node->changelist));

  SVN_ERR(svn_wc__upgrade_conflict_skel_from_raw(
                                &conflict_data,
                                db, wri_abspath,
                                actual_node->local_relpath,
                                actual_node->conflict_old,
                                actual_node->conflict_working,
                                actual_node->conflict_new,
                                actual_node->prop_reject,
                                actual_node->tree_conflict_data,
                                actual_node->tree_conflict_data
                                    ? strlen(actual_node->tree_conflict_data)
                                    : 0,
                                scratch_pool, scratch_pool));

  if (conflict_data)
    {
      svn_stringbuf_t *data = svn_skel__unparse(conflict_data, scratch_pool);

      SVN_ERR(svn_sqlite__bind_blob(stmt, 6, data->data, data->len));
    }

  /* Execute and reset the insert clause. */
  return svn_error_trace(svn_sqlite__insert(NULL, stmt));
}