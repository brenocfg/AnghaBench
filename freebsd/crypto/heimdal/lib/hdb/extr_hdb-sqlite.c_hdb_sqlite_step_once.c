#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ hdb_sqlite_db ;
struct TYPE_5__ {scalar_t__ hdb_db; } ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int hdb_sqlite_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_step_once(krb5_context context, HDB *db, sqlite3_stmt *statement)
{
    int ret;
    hdb_sqlite_db *hsdb = (hdb_sqlite_db *) db->hdb_db;

    ret = hdb_sqlite_step(context, hsdb->db, statement);
    sqlite3_clear_bindings(statement);
    sqlite3_reset(statement);

    return ret;
}