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
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void shellReset(
  int *pRc, 
  sqlite3_stmt *pStmt
){
  int rc = sqlite3_reset(pStmt);
  if( *pRc==SQLITE_OK ){
    if( rc!=SQLITE_OK ){
      sqlite3 *db = sqlite3_db_handle(pStmt);
      raw_printf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    *pRc = rc;
  }
}