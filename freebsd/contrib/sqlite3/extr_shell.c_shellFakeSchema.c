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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {char* z; } ;
typedef  TYPE_1__ ShellText ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  appendText (TYPE_1__*,char const*,char) ; 
 int /*<<< orphan*/  freeText (TYPE_1__*) ; 
 int /*<<< orphan*/  initText (TYPE_1__*) ; 
 char quoteChar (char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_stricmp (char const*,char*) ; 

__attribute__((used)) static char *shellFakeSchema(
  sqlite3 *db,            /* The database connection containing the vtab */
  const char *zSchema,    /* Schema of the database holding the vtab */
  const char *zName       /* The name of the virtual table */
){
  sqlite3_stmt *pStmt = 0;
  char *zSql;
  ShellText s;
  char cQuote;
  char *zDiv = "(";
  int nRow = 0;

  zSql = sqlite3_mprintf("PRAGMA \"%w\".table_info=%Q;",
                         zSchema ? zSchema : "main", zName);
  sqlite3_prepare_v2(db, zSql, -1, &pStmt, 0);
  sqlite3_free(zSql);
  initText(&s);
  if( zSchema ){
    cQuote = quoteChar(zSchema);
    if( cQuote && sqlite3_stricmp(zSchema,"temp")==0 ) cQuote = 0;
    appendText(&s, zSchema, cQuote);
    appendText(&s, ".", 0);
  }
  cQuote = quoteChar(zName);
  appendText(&s, zName, cQuote);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    const char *zCol = (const char*)sqlite3_column_text(pStmt, 1);
    nRow++;
    appendText(&s, zDiv, 0);
    zDiv = ",";
    cQuote = quoteChar(zCol);
    appendText(&s, zCol, cQuote);
  }
  appendText(&s, ")", 0);
  sqlite3_finalize(pStmt);
  if( nRow==0 ){
    freeText(&s);
    s.z = 0;
  }
  return s.z;
}