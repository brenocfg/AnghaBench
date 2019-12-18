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
struct TYPE_3__ {int /*<<< orphan*/  db; int /*<<< orphan*/  s3stmt; int /*<<< orphan*/  needs_reset; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SQLITE_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 

svn_error_t *
svn_sqlite__reset(svn_sqlite__stmt_t *stmt)
{
  /* No need to reset again after a first attempt */
  stmt->needs_reset = FALSE;

  /* Clear bindings first, as there are no documented reasons
     why this would ever fail, but keeping variable bindings
     when reset is not what we expect. */
  SQLITE_ERR(sqlite3_clear_bindings(stmt->s3stmt), stmt->db);

  /* Reset last, as this *will* fail if the statement failed since
     the last time it was reset, while reporting just the same failure.
     (In this case the statement is also properly reset).

     See the sqlite3_reset() documentation for more details. */
  SQLITE_ERR(sqlite3_reset(stmt->s3stmt), stmt->db);
  return SVN_NO_ERROR;
}