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
struct TYPE_3__ {int /*<<< orphan*/  db; int /*<<< orphan*/  s3stmt; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  sqlite_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ ,int) ; 

svn_error_t *
svn_sqlite__bind_revnum(svn_sqlite__stmt_t *stmt,
                        int slot,
                        svn_revnum_t value)
{
  if (SVN_IS_VALID_REVNUM(value))
    SQLITE_ERR(sqlite3_bind_int64(stmt->s3stmt, slot,
                                  (sqlite_int64)value), stmt->db);
  else
    SQLITE_ERR(sqlite3_bind_null(stmt->s3stmt, slot), stmt->db);

  return SVN_NO_ERROR;
}