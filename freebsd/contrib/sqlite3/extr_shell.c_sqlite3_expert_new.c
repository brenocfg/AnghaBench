#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int iSample; int /*<<< orphan*/  dbv; int /*<<< orphan*/  dbm; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ sqlite3expert ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_DBCONFIG_TRIGGER_EQP ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  idxAuthCallback ; 
 int idxCreateVtabSchema (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  idxFinalize (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ idxMalloc (int*,int) ; 
 int idxPrintfPrepareStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char**,char*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_db_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_expert_destroy (TYPE_1__*) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_set_authorizer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

sqlite3expert *sqlite3_expert_new(sqlite3 *db, char **pzErrmsg){
  int rc = SQLITE_OK;
  sqlite3expert *pNew;

  pNew = (sqlite3expert*)idxMalloc(&rc, sizeof(sqlite3expert));

  /* Open two in-memory databases to work with. The "vtab database" (dbv)
  ** will contain a virtual table corresponding to each real table in
  ** the user database schema, and a copy of each view. It is used to
  ** collect information regarding the WHERE, ORDER BY and other clauses
  ** of the user's query.
  */
  if( rc==SQLITE_OK ){
    pNew->db = db;
    pNew->iSample = 100;
    rc = sqlite3_open(":memory:", &pNew->dbv);
  }
  if( rc==SQLITE_OK ){
    rc = sqlite3_open(":memory:", &pNew->dbm);
    if( rc==SQLITE_OK ){
      sqlite3_db_config(pNew->dbm, SQLITE_DBCONFIG_TRIGGER_EQP, 1, (int*)0);
    }
  }
  

  /* Copy the entire schema of database [db] into [dbm]. */
  if( rc==SQLITE_OK ){
    sqlite3_stmt *pSql;
    rc = idxPrintfPrepareStmt(pNew->db, &pSql, pzErrmsg, 
        "SELECT sql FROM sqlite_master WHERE name NOT LIKE 'sqlite_%%'"
        " AND sql NOT LIKE 'CREATE VIRTUAL %%'"
    );
    while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pSql) ){
      const char *zSql = (const char*)sqlite3_column_text(pSql, 0);
      rc = sqlite3_exec(pNew->dbm, zSql, 0, 0, pzErrmsg);
    }
    idxFinalize(&rc, pSql);
  }

  /* Create the vtab schema */
  if( rc==SQLITE_OK ){
    rc = idxCreateVtabSchema(pNew, pzErrmsg);
  }

  /* Register the auth callback with dbv */
  if( rc==SQLITE_OK ){
    sqlite3_set_authorizer(pNew->dbv, idxAuthCallback, (void*)pNew);
  }

  /* If an error has occurred, free the new object and reutrn NULL. Otherwise,
  ** return the new sqlite3expert handle.  */
  if( rc!=SQLITE_OK ){
    sqlite3_expert_destroy(pNew);
    pNew = 0;
  }
  return pNew;
}