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

/* Variables and functions */
 int sqlite3_column_bytes (int /*<<< orphan*/ ,int) ; 

int
svn_sqlite__column_bytes(svn_sqlite__stmt_t *stmt, int column)
{
  return sqlite3_column_bytes(stmt->s3stmt, column);
}