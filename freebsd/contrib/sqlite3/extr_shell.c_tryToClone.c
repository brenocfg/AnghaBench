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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_db (int /*<<< orphan*/ *) ; 
 char const* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3_open (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tryToCloneData ; 
 int /*<<< orphan*/  tryToCloneSchema (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void tryToClone(ShellState *p, const char *zNewDb){
  int rc;
  sqlite3 *newDb = 0;
  if( access(zNewDb,0)==0 ){
    utf8_printf(stderr, "File \"%s\" already exists.\n", zNewDb);
    return;
  }
  rc = sqlite3_open(zNewDb, &newDb);
  if( rc ){
    utf8_printf(stderr, "Cannot create output database: %s\n",
            sqlite3_errmsg(newDb));
  }else{
    sqlite3_exec(p->db, "PRAGMA writable_schema=ON;", 0, 0, 0);
    sqlite3_exec(newDb, "BEGIN EXCLUSIVE;", 0, 0, 0);
    tryToCloneSchema(p, newDb, "type='table'", tryToCloneData);
    tryToCloneSchema(p, newDb, "type!='table'", 0);
    sqlite3_exec(newDb, "COMMIT;", 0, 0, 0);
    sqlite3_exec(p->db, "PRAGMA writable_schema=OFF;", 0, 0, 0);
  }
  close_db(newDb);
}