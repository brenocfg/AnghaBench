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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db_int(ShellState *p, const char *zSql){
  sqlite3_stmt *pStmt;
  int res = 0;
  sqlite3_prepare_v2(p->db, zSql, -1, &pStmt, 0);
  if( pStmt && sqlite3_step(pStmt)==SQLITE_ROW ){
    res = sqlite3_column_int(pStmt,0);
  }
  sqlite3_finalize(pStmt);
  return res;
}