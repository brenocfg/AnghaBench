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
struct TYPE_4__ {int /*<<< orphan*/  s3stmt; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ svn_sqlite__column_is_null (TYPE_1__*,int) ; 

svn_revnum_t
svn_sqlite__column_revnum(svn_sqlite__stmt_t *stmt, int column)
{
  if (svn_sqlite__column_is_null(stmt, column))
    return SVN_INVALID_REVNUM;
  return (svn_revnum_t) sqlite3_column_int64(stmt->s3stmt, column);
}