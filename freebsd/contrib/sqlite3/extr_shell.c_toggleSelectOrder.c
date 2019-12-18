#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zStmt ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void toggleSelectOrder(sqlite3 *db){
  sqlite3_stmt *pStmt = 0;
  int iSetting = 0;
  char zStmt[100];
  sqlite3_prepare_v2(db, "PRAGMA reverse_unordered_selects", -1, &pStmt, 0);
  if( sqlite3_step(pStmt)==SQLITE_ROW ){
    iSetting = sqlite3_column_int(pStmt, 0);
  }
  sqlite3_finalize(pStmt);
  sqlite3_snprintf(sizeof(zStmt), zStmt,
       "PRAGMA reverse_unordered_selects(%d)", !iSetting);
  sqlite3_exec(db, zStmt, 0, 0, 0);
}