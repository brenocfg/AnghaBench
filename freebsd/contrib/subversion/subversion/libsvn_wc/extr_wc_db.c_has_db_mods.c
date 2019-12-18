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
struct TYPE_3__ {int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_SUBTREE_HAS_PROP_MODIFICATIONS ; 
 int /*<<< orphan*/  STMT_SUBTREE_HAS_TREE_MODIFICATIONS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
has_db_mods(svn_boolean_t *is_modified,
            svn_wc__db_wcroot_t *wcroot,
            const char *local_relpath,
            apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  /* Check for additions or deletions. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SUBTREE_HAS_TREE_MODIFICATIONS));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  /* If this query returns a row, the working copy is modified. */
  SVN_ERR(svn_sqlite__step(is_modified, stmt));
  SVN_ERR(svn_sqlite__reset(stmt));

  if (! *is_modified)
    {
      /* Check for property modifications. */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SUBTREE_HAS_PROP_MODIFICATIONS));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      /* If this query returns a row, the working copy is modified. */
      SVN_ERR(svn_sqlite__step(is_modified, stmt));
      SVN_ERR(svn_sqlite__reset(stmt));
    }

  return SVN_NO_ERROR;
}