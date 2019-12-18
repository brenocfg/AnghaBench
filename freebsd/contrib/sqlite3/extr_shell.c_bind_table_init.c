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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_DBCONFIG_WRITABLE_SCHEMA ; 
 int /*<<< orphan*/  sqlite3_db_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bind_table_init(ShellState *p){
  int wrSchema = 0;
  sqlite3_db_config(p->db, SQLITE_DBCONFIG_WRITABLE_SCHEMA, -1, &wrSchema);
  sqlite3_db_config(p->db, SQLITE_DBCONFIG_WRITABLE_SCHEMA, 1, 0);
  sqlite3_exec(p->db,
    "CREATE TABLE IF NOT EXISTS temp.sqlite_parameters(\n"
    "  key TEXT PRIMARY KEY,\n"
    "  value ANY\n"
    ") WITHOUT ROWID;",
    0, 0, 0);
  sqlite3_db_config(p->db, SQLITE_DBCONFIG_WRITABLE_SCHEMA, wrSchema, 0);
}