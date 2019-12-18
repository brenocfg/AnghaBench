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
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  idxFinalize (int*,int /*<<< orphan*/ *) ; 
 int idxPrepareStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char**,char const*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idxLargestIndex(sqlite3 *db, int *pnMax, char **pzErr){
  int rc = SQLITE_OK;
  const char *zMax = 
    "SELECT max(i.seqno) FROM "
    "  sqlite_master AS s, "
    "  pragma_index_list(s.name) AS l, "
    "  pragma_index_info(l.name) AS i "
    "WHERE s.type = 'table'";
  sqlite3_stmt *pMax = 0;

  *pnMax = 0;
  rc = idxPrepareStmt(db, &pMax, pzErr, zMax);
  if( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pMax) ){
    *pnMax = sqlite3_column_int(pMax, 0) + 1;
  }
  idxFinalize(&rc, pMax);

  return rc;
}