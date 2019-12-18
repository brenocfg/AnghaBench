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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
#define  SQLITE_BLOB 132 
 int SQLITE_DONE ; 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char) ; 
 int /*<<< orphan*/  shell_out_of_memory () ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_double (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_extended_errcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen30 (char const*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static void tryToCloneData(
  ShellState *p,
  sqlite3 *newDb,
  const char *zTable
){
  sqlite3_stmt *pQuery = 0;
  sqlite3_stmt *pInsert = 0;
  char *zQuery = 0;
  char *zInsert = 0;
  int rc;
  int i, j, n;
  int nTable = strlen30(zTable);
  int k = 0;
  int cnt = 0;
  const int spinRate = 10000;

  zQuery = sqlite3_mprintf("SELECT * FROM \"%w\"", zTable);
  rc = sqlite3_prepare_v2(p->db, zQuery, -1, &pQuery, 0);
  if( rc ){
    utf8_printf(stderr, "Error %d: %s on [%s]\n",
            sqlite3_extended_errcode(p->db), sqlite3_errmsg(p->db),
            zQuery);
    goto end_data_xfer;
  }
  n = sqlite3_column_count(pQuery);
  zInsert = sqlite3_malloc64(200 + nTable + n*3);
  if( zInsert==0 ) shell_out_of_memory();
  sqlite3_snprintf(200+nTable,zInsert,
                   "INSERT OR IGNORE INTO \"%s\" VALUES(?", zTable);
  i = strlen30(zInsert);
  for(j=1; j<n; j++){
    memcpy(zInsert+i, ",?", 2);
    i += 2;
  }
  memcpy(zInsert+i, ");", 3);
  rc = sqlite3_prepare_v2(newDb, zInsert, -1, &pInsert, 0);
  if( rc ){
    utf8_printf(stderr, "Error %d: %s on [%s]\n",
            sqlite3_extended_errcode(newDb), sqlite3_errmsg(newDb),
            zQuery);
    goto end_data_xfer;
  }
  for(k=0; k<2; k++){
    while( (rc = sqlite3_step(pQuery))==SQLITE_ROW ){
      for(i=0; i<n; i++){
        switch( sqlite3_column_type(pQuery, i) ){
          case SQLITE_NULL: {
            sqlite3_bind_null(pInsert, i+1);
            break;
          }
          case SQLITE_INTEGER: {
            sqlite3_bind_int64(pInsert, i+1, sqlite3_column_int64(pQuery,i));
            break;
          }
          case SQLITE_FLOAT: {
            sqlite3_bind_double(pInsert, i+1, sqlite3_column_double(pQuery,i));
            break;
          }
          case SQLITE_TEXT: {
            sqlite3_bind_text(pInsert, i+1,
                             (const char*)sqlite3_column_text(pQuery,i),
                             -1, SQLITE_STATIC);
            break;
          }
          case SQLITE_BLOB: {
            sqlite3_bind_blob(pInsert, i+1, sqlite3_column_blob(pQuery,i),
                                            sqlite3_column_bytes(pQuery,i),
                                            SQLITE_STATIC);
            break;
          }
        }
      } /* End for */
      rc = sqlite3_step(pInsert);
      if( rc!=SQLITE_OK && rc!=SQLITE_ROW && rc!=SQLITE_DONE ){
        utf8_printf(stderr, "Error %d: %s\n", sqlite3_extended_errcode(newDb),
                        sqlite3_errmsg(newDb));
      }
      sqlite3_reset(pInsert);
      cnt++;
      if( (cnt%spinRate)==0 ){
        printf("%c\b", "|/-\\"[(cnt/spinRate)%4]);
        fflush(stdout);
      }
    } /* End while */
    if( rc==SQLITE_DONE ) break;
    sqlite3_finalize(pQuery);
    sqlite3_free(zQuery);
    zQuery = sqlite3_mprintf("SELECT * FROM \"%w\" ORDER BY rowid DESC;",
                             zTable);
    rc = sqlite3_prepare_v2(p->db, zQuery, -1, &pQuery, 0);
    if( rc ){
      utf8_printf(stderr, "Warning: cannot step \"%s\" backwards", zTable);
      break;
    }
  } /* End for(k=0...) */

end_data_xfer:
  sqlite3_finalize(pQuery);
  sqlite3_finalize(pInsert);
  sqlite3_free(zQuery);
  sqlite3_free(zInsert);
}