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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void shellPrepare(
  sqlite3 *db, 
  int *pRc, 
  const char *zSql, 
  sqlite3_stmt **ppStmt
){
  *ppStmt = 0;
  if( *pRc==SQLITE_OK ){
    int rc = sqlite3_prepare_v2(db, zSql, -1, ppStmt, 0);
    if( rc!=SQLITE_OK ){
      raw_printf(stderr, "sql error: %s (%d)\n", 
          sqlite3_errmsg(db), sqlite3_errcode(db)
      );
      *pRc = rc;
    }
  }
}