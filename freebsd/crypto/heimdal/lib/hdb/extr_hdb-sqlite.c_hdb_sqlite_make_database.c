#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_5__ {scalar_t__ version; int /*<<< orphan*/ * db_file; scalar_t__ db; int /*<<< orphan*/  get_version; int /*<<< orphan*/  get_all_entries; int /*<<< orphan*/  remove; int /*<<< orphan*/  update_entry; int /*<<< orphan*/  delete_aliases; int /*<<< orphan*/  add_alias; int /*<<< orphan*/  add_principal; int /*<<< orphan*/  add_entry; int /*<<< orphan*/  get_ids; int /*<<< orphan*/  fetch; } ;
typedef  TYPE_1__ hdb_sqlite_db ;
struct TYPE_6__ {scalar_t__ hdb_db; } ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HDBSQLITE_ADD_ALIAS ; 
 int /*<<< orphan*/  HDBSQLITE_ADD_ENTRY ; 
 int /*<<< orphan*/  HDBSQLITE_ADD_PRINCIPAL ; 
 int /*<<< orphan*/  HDBSQLITE_CREATE_TABLES ; 
 int /*<<< orphan*/  HDBSQLITE_CREATE_TRIGGERS ; 
 int /*<<< orphan*/  HDBSQLITE_DELETE_ALIASES ; 
 int /*<<< orphan*/  HDBSQLITE_FETCH ; 
 int /*<<< orphan*/  HDBSQLITE_GET_ALL_ENTRIES ; 
 int /*<<< orphan*/  HDBSQLITE_GET_IDS ; 
 int /*<<< orphan*/  HDBSQLITE_GET_VERSION ; 
 int /*<<< orphan*/  HDBSQLITE_REMOVE ; 
 int /*<<< orphan*/  HDBSQLITE_UPDATE_ENTRY ; 
 scalar_t__ HDBSQLITE_VERSION ; 
 int /*<<< orphan*/  SQLITE_OPEN_CREATE ; 
 int SQLITE_ROW ; 
 int hdb_sqlite_exec_stmt (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int hdb_sqlite_open_database (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int hdb_sqlite_prepare_stmt (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hdb_sqlite_step (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  sqlite3_close (scalar_t__) ; 
 scalar_t__ sqlite3_column_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_make_database(krb5_context context, HDB *db, const char *filename)
{
    int ret;
    int created_file = 0;
    hdb_sqlite_db *hsdb = (hdb_sqlite_db *) db->hdb_db;

    hsdb->db_file = strdup(filename);
    if(hsdb->db_file == NULL)
        return ENOMEM;

    ret = hdb_sqlite_open_database(context, db, 0);
    if (ret) {
        ret = hdb_sqlite_open_database(context, db, SQLITE_OPEN_CREATE);
        if (ret) goto out;

        created_file = 1;

        ret = hdb_sqlite_exec_stmt(context, hsdb->db,
                                   HDBSQLITE_CREATE_TABLES,
                                   EINVAL);
        if (ret) goto out;

        ret = hdb_sqlite_exec_stmt(context, hsdb->db,
                                   HDBSQLITE_CREATE_TRIGGERS,
                                   EINVAL);
        if (ret) goto out;
    }

    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->get_version,
                                  HDBSQLITE_GET_VERSION);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->fetch,
                                  HDBSQLITE_FETCH);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->get_ids,
                                  HDBSQLITE_GET_IDS);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->add_entry,
                                  HDBSQLITE_ADD_ENTRY);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->add_principal,
                                  HDBSQLITE_ADD_PRINCIPAL);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->add_alias,
                                  HDBSQLITE_ADD_ALIAS);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->delete_aliases,
                                  HDBSQLITE_DELETE_ALIASES);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->update_entry,
                                  HDBSQLITE_UPDATE_ENTRY);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->remove,
                                  HDBSQLITE_REMOVE);
    if (ret) goto out;
    ret = hdb_sqlite_prepare_stmt(context, hsdb->db,
                                  &hsdb->get_all_entries,
                                  HDBSQLITE_GET_ALL_ENTRIES);
    if (ret) goto out;

    ret = hdb_sqlite_step(context, hsdb->db, hsdb->get_version);
    if(ret == SQLITE_ROW) {
        hsdb->version = sqlite3_column_double(hsdb->get_version, 0);
    }
    sqlite3_reset(hsdb->get_version);
    ret = 0;

    if(hsdb->version != HDBSQLITE_VERSION) {
        ret = EINVAL;
        krb5_set_error_message(context, ret, "HDBSQLITE_VERSION mismatch");
    }

    if(ret) goto out;

    return 0;

 out:
    if (hsdb->db)
        sqlite3_close(hsdb->db);
    if (created_file)
        unlink(hsdb->db_file);

    return ret;
}