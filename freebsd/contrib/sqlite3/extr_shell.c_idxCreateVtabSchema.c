#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dbv; TYPE_3__* pTable; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ sqlite3expert ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_9__ {int nCol; TYPE_1__* aCol; struct TYPE_9__* pNext; } ;
struct TYPE_7__ {int /*<<< orphan*/  zColl; int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ IdxTable ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 char* idxAppendText (int*,char*,char*,...) ; 
 int /*<<< orphan*/  idxFinalize (int*,int /*<<< orphan*/ *) ; 
 int idxGetTableInfo (int /*<<< orphan*/ ,char const*,TYPE_3__**,char**) ; 
 int idxPrepareStmt (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char**,char*) ; 
 int idxRegisterVtab (TYPE_2__*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idxCreateVtabSchema(sqlite3expert *p, char **pzErrmsg){
  int rc = idxRegisterVtab(p);
  sqlite3_stmt *pSchema = 0;

  /* For each table in the main db schema:
  **
  **   1) Add an entry to the p->pTable list, and
  **   2) Create the equivalent virtual table in dbv.
  */
  rc = idxPrepareStmt(p->db, &pSchema, pzErrmsg,
      "SELECT type, name, sql, 1 FROM sqlite_master "
      "WHERE type IN ('table','view') AND name NOT LIKE 'sqlite_%%' "
      " UNION ALL "
      "SELECT type, name, sql, 2 FROM sqlite_master "
      "WHERE type = 'trigger'"
      "  AND tbl_name IN(SELECT name FROM sqlite_master WHERE type = 'view') "
      "ORDER BY 4, 1"
  );
  while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pSchema) ){
    const char *zType = (const char*)sqlite3_column_text(pSchema, 0);
    const char *zName = (const char*)sqlite3_column_text(pSchema, 1);
    const char *zSql = (const char*)sqlite3_column_text(pSchema, 2);

    if( zType[0]=='v' || zType[1]=='r' ){
      rc = sqlite3_exec(p->dbv, zSql, 0, 0, pzErrmsg);
    }else{
      IdxTable *pTab;
      rc = idxGetTableInfo(p->db, zName, &pTab, pzErrmsg);
      if( rc==SQLITE_OK ){
        int i;
        char *zInner = 0;
        char *zOuter = 0;
        pTab->pNext = p->pTable;
        p->pTable = pTab;

        /* The statement the vtab will pass to sqlite3_declare_vtab() */
        zInner = idxAppendText(&rc, 0, "CREATE TABLE x(");
        for(i=0; i<pTab->nCol; i++){
          zInner = idxAppendText(&rc, zInner, "%s%Q COLLATE %s", 
              (i==0 ? "" : ", "), pTab->aCol[i].zName, pTab->aCol[i].zColl
          );
        }
        zInner = idxAppendText(&rc, zInner, ")");

        /* The CVT statement to create the vtab */
        zOuter = idxAppendText(&rc, 0, 
            "CREATE VIRTUAL TABLE %Q USING expert(%Q)", zName, zInner
        );
        if( rc==SQLITE_OK ){
          rc = sqlite3_exec(p->dbv, zOuter, 0, 0, pzErrmsg);
        }
        sqlite3_free(zInner);
        sqlite3_free(zOuter);
      }
    }
  }
  idxFinalize(&rc, pSchema);
  return rc;
}