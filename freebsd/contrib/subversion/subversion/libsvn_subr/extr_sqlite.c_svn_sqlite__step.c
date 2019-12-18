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
struct TYPE_6__ {int /*<<< orphan*/  needs_reset; TYPE_1__* db; int /*<<< orphan*/  s3stmt; } ;
typedef  TYPE_2__ svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  db3; } ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_ERROR_CODE (int) ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__reset (TYPE_2__*) ; 

svn_error_t *
svn_sqlite__step(svn_boolean_t *got_row, svn_sqlite__stmt_t *stmt)
{
  int sqlite_result = sqlite3_step(stmt->s3stmt);

  if (sqlite_result != SQLITE_DONE && sqlite_result != SQLITE_ROW)
    {
      svn_error_t *err1, *err2;

      err1 = svn_error_createf(SQLITE_ERROR_CODE(sqlite_result), NULL,
                               "sqlite[S%d]: %s",
                               sqlite_result, sqlite3_errmsg(stmt->db->db3));
      err2 = svn_sqlite__reset(stmt);
      return svn_error_compose_create(err1, err2);
    }

  *got_row = (sqlite_result == SQLITE_ROW);
  stmt->needs_reset = TRUE;

  return SVN_NO_ERROR;
}