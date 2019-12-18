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
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int SQLITE_DONE ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned char* sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_extended_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char*,unsigned char const*,...) ; 

__attribute__((used)) static void tryToCloneSchema(
  ShellState *p,
  sqlite3 *newDb,
  const char *zWhere,
  void (*xForEach)(ShellState*,sqlite3*,const char*)
){
  sqlite3_stmt *pQuery = 0;
  char *zQuery = 0;
  int rc;
  const unsigned char *zName;
  const unsigned char *zSql;
  char *zErrMsg = 0;

  zQuery = sqlite3_mprintf("SELECT name, sql FROM sqlite_master"
                           " WHERE %s", zWhere);
  rc = sqlite3_prepare_v2(p->db, zQuery, -1, &pQuery, 0);
  if( rc ){
    utf8_printf(stderr, "Error: (%d) %s on [%s]\n",
                    sqlite3_extended_errcode(p->db), sqlite3_errmsg(p->db),
                    zQuery);
    goto end_schema_xfer;
  }
  while( (rc = sqlite3_step(pQuery))==SQLITE_ROW ){
    zName = sqlite3_column_text(pQuery, 0);
    zSql = sqlite3_column_text(pQuery, 1);
    printf("%s... ", zName); fflush(stdout);
    sqlite3_exec(newDb, (const char*)zSql, 0, 0, &zErrMsg);
    if( zErrMsg ){
      utf8_printf(stderr, "Error: %s\nSQL: [%s]\n", zErrMsg, zSql);
      sqlite3_free(zErrMsg);
      zErrMsg = 0;
    }
    if( xForEach ){
      xForEach(p, newDb, (const char*)zName);
    }
    printf("done\n");
  }
  if( rc!=SQLITE_DONE ){
    sqlite3_finalize(pQuery);
    sqlite3_free(zQuery);
    zQuery = sqlite3_mprintf("SELECT name, sql FROM sqlite_master"
                             " WHERE %s ORDER BY rowid DESC", zWhere);
    rc = sqlite3_prepare_v2(p->db, zQuery, -1, &pQuery, 0);
    if( rc ){
      utf8_printf(stderr, "Error: (%d) %s on [%s]\n",
                      sqlite3_extended_errcode(p->db), sqlite3_errmsg(p->db),
                      zQuery);
      goto end_schema_xfer;
    }
    while( (rc = sqlite3_step(pQuery))==SQLITE_ROW ){
      zName = sqlite3_column_text(pQuery, 0);
      zSql = sqlite3_column_text(pQuery, 1);
      printf("%s... ", zName); fflush(stdout);
      sqlite3_exec(newDb, (const char*)zSql, 0, 0, &zErrMsg);
      if( zErrMsg ){
        utf8_printf(stderr, "Error: %s\nSQL: [%s]\n", zErrMsg, zSql);
        sqlite3_free(zErrMsg);
        zErrMsg = 0;
      }
      if( xForEach ){
        xForEach(p, newDb, (const char*)zName);
      }
      printf("done\n");
    }
  }
end_schema_xfer:
  sqlite3_finalize(pQuery);
  sqlite3_free(zQuery);
}