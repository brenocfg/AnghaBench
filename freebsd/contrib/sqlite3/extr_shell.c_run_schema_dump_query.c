#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  out; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int SQLITE_CORRUPT ; 
 int /*<<< orphan*/  dump_callback ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*) ; 
 int strlen30 (char const*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int run_schema_dump_query(
  ShellState *p,
  const char *zQuery
){
  int rc;
  char *zErr = 0;
  rc = sqlite3_exec(p->db, zQuery, dump_callback, p, &zErr);
  if( rc==SQLITE_CORRUPT ){
    char *zQ2;
    int len = strlen30(zQuery);
    raw_printf(p->out, "/****** CORRUPTION ERROR *******/\n");
    if( zErr ){
      utf8_printf(p->out, "/****** %s ******/\n", zErr);
      sqlite3_free(zErr);
      zErr = 0;
    }
    zQ2 = malloc( len+100 );
    if( zQ2==0 ) return rc;
    sqlite3_snprintf(len+100, zQ2, "%s ORDER BY rowid DESC", zQuery);
    rc = sqlite3_exec(p->db, zQ2, dump_callback, p, &zErr);
    if( rc ){
      utf8_printf(p->out, "/****** ERROR: %s ******/\n", zErr);
    }else{
      rc = SQLITE_CORRUPT;
    }
    sqlite3_free(zErr);
    free(zQ2);
  }
  return rc;
}