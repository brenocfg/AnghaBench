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
struct TYPE_5__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INSERT_ACTUAL_CONFLICT ; 
 int /*<<< orphan*/  STMT_SELECT_ACTUAL_NODE ; 
 int /*<<< orphan*/  STMT_UPDATE_ACTUAL_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_skel__unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bind_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_is_complete (scalar_t__*,int /*<<< orphan*/  const*) ; 

svn_error_t *
svn_wc__db_mark_conflict_internal(svn_wc__db_wcroot_t *wcroot,
                                  const char *local_relpath,
                                  const svn_skel_t *conflict_skel,
                                  apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t got_row;
  svn_boolean_t is_complete;

  SVN_ERR(svn_wc__conflict_skel_is_complete(&is_complete, conflict_skel));
  SVN_ERR_ASSERT(is_complete);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_ACTUAL_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&got_row, stmt));
  SVN_ERR(svn_sqlite__reset(stmt));

  if (got_row)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_UPDATE_ACTUAL_CONFLICT));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
    }
  else
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_INSERT_ACTUAL_CONFLICT));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      if (*local_relpath != '\0')
        SVN_ERR(svn_sqlite__bind_text(stmt, 4,
                                      svn_relpath_dirname(local_relpath,
                                                          scratch_pool)));
    }

  {
    svn_stringbuf_t *sb = svn_skel__unparse(conflict_skel, scratch_pool);

    SVN_ERR(svn_sqlite__bind_blob(stmt, 3, sb->data, sb->len));
  }

  SVN_ERR(svn_sqlite__update(NULL, stmt));

  return SVN_NO_ERROR;
}