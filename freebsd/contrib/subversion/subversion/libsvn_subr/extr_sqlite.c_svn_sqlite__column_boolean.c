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
struct TYPE_3__ {int /*<<< orphan*/  s3stmt; } ;
typedef  TYPE_1__ svn_sqlite__stmt_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ sqlite3_column_int64 (int /*<<< orphan*/ ,int) ; 

svn_boolean_t
svn_sqlite__column_boolean(svn_sqlite__stmt_t *stmt, int column)
{
  return sqlite3_column_int64(stmt->s3stmt, column) != 0;
}