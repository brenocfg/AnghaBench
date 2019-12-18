#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int writableSchema; char* zDestTable; int mode; int cMode; int /*<<< orphan*/  nErr; int /*<<< orphan*/  db; int /*<<< orphan*/  out; } ;
struct TYPE_8__ {char* z; } ;
typedef  TYPE_1__ ShellText ;
typedef  TYPE_2__ ShellState ;

/* Variables and functions */
 int MODE_Insert ; 
 int SQLITE_CORRUPT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (char**) ; 
 int /*<<< orphan*/  appendText (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeColumnList (char**) ; 
 int /*<<< orphan*/  freeText (TYPE_1__*) ; 
 int /*<<< orphan*/  initText (TYPE_1__*) ; 
 int /*<<< orphan*/  printSchemaLine (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  quoteChar (char const*) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*) ; 
 int shell_exec (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*,char const*,char const*) ; 
 scalar_t__ sqlite3_strglob (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char** tableColumnList (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  toggleSelectOrder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int dump_callback(void *pArg, int nArg, char **azArg, char **azNotUsed){
  int rc;
  const char *zTable;
  const char *zType;
  const char *zSql;
  ShellState *p = (ShellState *)pArg;

  UNUSED_PARAMETER(azNotUsed);
  if( nArg!=3 || azArg==0 ) return 0;
  zTable = azArg[0];
  zType = azArg[1];
  zSql = azArg[2];

  if( strcmp(zTable, "sqlite_sequence")==0 ){
    raw_printf(p->out, "DELETE FROM sqlite_sequence;\n");
  }else if( sqlite3_strglob("sqlite_stat?", zTable)==0 ){
    raw_printf(p->out, "ANALYZE sqlite_master;\n");
  }else if( strncmp(zTable, "sqlite_", 7)==0 ){
    return 0;
  }else if( strncmp(zSql, "CREATE VIRTUAL TABLE", 20)==0 ){
    char *zIns;
    if( !p->writableSchema ){
      raw_printf(p->out, "PRAGMA writable_schema=ON;\n");
      p->writableSchema = 1;
    }
    zIns = sqlite3_mprintf(
       "INSERT INTO sqlite_master(type,name,tbl_name,rootpage,sql)"
       "VALUES('table','%q','%q',0,'%q');",
       zTable, zTable, zSql);
    utf8_printf(p->out, "%s\n", zIns);
    sqlite3_free(zIns);
    return 0;
  }else{
    printSchemaLine(p->out, zSql, ";\n");
  }

  if( strcmp(zType, "table")==0 ){
    ShellText sSelect;
    ShellText sTable;
    char **azCol;
    int i;
    char *savedDestTable;
    int savedMode;

    azCol = tableColumnList(p, zTable);
    if( azCol==0 ){
      p->nErr++;
      return 0;
    }

    /* Always quote the table name, even if it appears to be pure ascii,
    ** in case it is a keyword. Ex:  INSERT INTO "table" ... */
    initText(&sTable);
    appendText(&sTable, zTable, quoteChar(zTable));
    /* If preserving the rowid, add a column list after the table name.
    ** In other words:  "INSERT INTO tab(rowid,a,b,c,...) VALUES(...)"
    ** instead of the usual "INSERT INTO tab VALUES(...)".
    */
    if( azCol[0] ){
      appendText(&sTable, "(", 0);
      appendText(&sTable, azCol[0], 0);
      for(i=1; azCol[i]; i++){
        appendText(&sTable, ",", 0);
        appendText(&sTable, azCol[i], quoteChar(azCol[i]));
      }
      appendText(&sTable, ")", 0);
    }

    /* Build an appropriate SELECT statement */
    initText(&sSelect);
    appendText(&sSelect, "SELECT ", 0);
    if( azCol[0] ){
      appendText(&sSelect, azCol[0], 0);
      appendText(&sSelect, ",", 0);
    }
    for(i=1; azCol[i]; i++){
      appendText(&sSelect, azCol[i], quoteChar(azCol[i]));
      if( azCol[i+1] ){
        appendText(&sSelect, ",", 0);
      }
    }
    freeColumnList(azCol);
    appendText(&sSelect, " FROM ", 0);
    appendText(&sSelect, zTable, quoteChar(zTable));

    savedDestTable = p->zDestTable;
    savedMode = p->mode;
    p->zDestTable = sTable.z;
    p->mode = p->cMode = MODE_Insert;
    rc = shell_exec(p, sSelect.z, 0);
    if( (rc&0xff)==SQLITE_CORRUPT ){
      raw_printf(p->out, "/****** CORRUPTION ERROR *******/\n");
      toggleSelectOrder(p->db);
      shell_exec(p, sSelect.z, 0);
      toggleSelectOrder(p->db);
    }
    p->zDestTable = savedDestTable;
    p->mode = savedMode;
    freeText(&sTable);
    freeText(&sSelect);
    if( rc ) p->nErr++;
  }
  return 0;
}