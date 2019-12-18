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
typedef  int /*<<< orphan*/  zNum ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int sqlite3_bind_parameter_count (int /*<<< orphan*/ *) ; 
 char* sqlite3_bind_parameter_name (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_value (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_table_column_metadata (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bind_prepared_stmt(ShellState *pArg, sqlite3_stmt *pStmt){
  int nVar;
  int i;
  int rc;
  sqlite3_stmt *pQ = 0;

  nVar = sqlite3_bind_parameter_count(pStmt);
  if( nVar==0 ) return;  /* Nothing to do */
  if( sqlite3_table_column_metadata(pArg->db, "TEMP", "sqlite_parameters",
                                    "key", 0, 0, 0, 0, 0)!=SQLITE_OK ){
    return; /* Parameter table does not exist */
  }
  rc = sqlite3_prepare_v2(pArg->db,
          "SELECT value FROM temp.sqlite_parameters"
          " WHERE key=?1", -1, &pQ, 0);
  if( rc || pQ==0 ) return;
  for(i=1; i<=nVar; i++){
    char zNum[30];
    const char *zVar = sqlite3_bind_parameter_name(pStmt, i);
    if( zVar==0 ){
      sqlite3_snprintf(sizeof(zNum),zNum,"?%d",i);
      zVar = zNum;
    }
    sqlite3_bind_text(pQ, 1, zVar, -1, SQLITE_STATIC);
    if( sqlite3_step(pQ)==SQLITE_ROW ){
      sqlite3_bind_value(pStmt, i, sqlite3_column_value(pQ, 0));
    }else{
      sqlite3_bind_null(pStmt, i);
    }
    sqlite3_reset(pQ);
  }
  sqlite3_finalize(pQ);
}