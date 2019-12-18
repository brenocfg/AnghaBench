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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int /*<<< orphan*/  db; int /*<<< orphan*/  get_all_entries; int /*<<< orphan*/  remove; int /*<<< orphan*/  update_entry; int /*<<< orphan*/  delete_aliases; int /*<<< orphan*/  add_alias; int /*<<< orphan*/  add_principal; int /*<<< orphan*/  add_entry; int /*<<< orphan*/  get_ids; int /*<<< orphan*/  fetch; int /*<<< orphan*/  get_version; } ;
typedef  TYPE_1__ hdb_sqlite_db ;
struct TYPE_5__ {scalar_t__ hdb_db; } ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_close_database(krb5_context context, HDB *db)
{
    hdb_sqlite_db *hsdb = (hdb_sqlite_db *) db->hdb_db;

    sqlite3_finalize(hsdb->get_version);
    sqlite3_finalize(hsdb->fetch);
    sqlite3_finalize(hsdb->get_ids);
    sqlite3_finalize(hsdb->add_entry);
    sqlite3_finalize(hsdb->add_principal);
    sqlite3_finalize(hsdb->add_alias);
    sqlite3_finalize(hsdb->delete_aliases);
    sqlite3_finalize(hsdb->update_entry);
    sqlite3_finalize(hsdb->remove);
    sqlite3_finalize(hsdb->get_all_entries);

    sqlite3_close(hsdb->db);

    return 0;
}