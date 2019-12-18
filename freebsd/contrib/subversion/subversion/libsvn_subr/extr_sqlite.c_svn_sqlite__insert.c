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
struct TYPE_7__ {TYPE_1__* db; } ;
typedef  TYPE_2__ svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  db3; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,TYPE_2__*) ; 

svn_error_t *
svn_sqlite__insert(apr_int64_t *row_id, svn_sqlite__stmt_t *stmt)
{
  svn_boolean_t got_row;

  SVN_ERR(svn_sqlite__step(&got_row, stmt));
  if (row_id)
    *row_id = sqlite3_last_insert_rowid(stmt->db->db3);

  return svn_error_trace(svn_sqlite__reset(stmt));
}