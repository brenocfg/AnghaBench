#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int krb5_error_code ;
struct TYPE_19__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_20__ {int /*<<< orphan*/  db; int /*<<< orphan*/ * add_alias; int /*<<< orphan*/ * update_entry; int /*<<< orphan*/ * delete_aliases; int /*<<< orphan*/ * add_principal; int /*<<< orphan*/ * add_entry; int /*<<< orphan*/ * get_ids; } ;
typedef  TYPE_3__ hdb_sqlite_db ;
struct TYPE_17__ {int /*<<< orphan*/ * principal; } ;
struct TYPE_21__ {TYPE_12__ entry; } ;
typedef  TYPE_4__ hdb_entry_ex ;
struct TYPE_23__ {scalar_t__ hdb_db; } ;
struct TYPE_18__ {int len; int /*<<< orphan*/ * val; } ;
struct TYPE_22__ {TYPE_1__ aliases; } ;
typedef  TYPE_5__ HDB_Ext_Aliases ;
typedef  TYPE_6__ HDB ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int HDB_F_REPLACE ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  free (char*) ; 
 int hdb_entry2value (int /*<<< orphan*/ ,TYPE_12__*,TYPE_2__*) ; 
 int hdb_entry_get_aliases (TYPE_12__*,TYPE_5__ const**) ; 
 int hdb_seal_keys (int /*<<< orphan*/ ,TYPE_6__*,TYPE_12__*) ; 
 int hdb_sqlite_exec_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int hdb_sqlite_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hdb_sqlite_step_once (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_store(krb5_context context, HDB *db, unsigned flags,
                 hdb_entry_ex *entry)
{
    int ret;
    int i;
    sqlite_int64 entry_id;
    char *principal_string = NULL;
    char *alias_string;
    const HDB_Ext_Aliases *aliases;

    hdb_sqlite_db *hsdb = (hdb_sqlite_db *)(db->hdb_db);
    krb5_data value;
    sqlite3_stmt *get_ids = hsdb->get_ids;

    ret = hdb_sqlite_exec_stmt(context, hsdb->db,
                               "BEGIN IMMEDIATE TRANSACTION", EINVAL);
    if(ret != SQLITE_OK) {
	ret = EINVAL;
        krb5_set_error_message(context, ret,
			       "SQLite BEGIN TRANSACTION failed: %s",
			       sqlite3_errmsg(hsdb->db));
        goto rollback;
    }

    ret = krb5_unparse_name(context,
                            entry->entry.principal, &principal_string);
    if (ret) {
        goto rollback;
    }

    ret = hdb_seal_keys(context, db, &entry->entry);
    if(ret) {
        goto rollback;
    }

    ret = hdb_entry2value(context, &entry->entry, &value);
    if(ret) {
        goto rollback;
    }

    sqlite3_bind_text(get_ids, 1, principal_string, -1, SQLITE_STATIC);
    ret = hdb_sqlite_step(context, hsdb->db, get_ids);

    if(ret == SQLITE_DONE) { /* No such principal */

        sqlite3_bind_blob(hsdb->add_entry, 1,
                          value.data, value.length, SQLITE_STATIC);
        ret = hdb_sqlite_step(context, hsdb->db, hsdb->add_entry);
        sqlite3_clear_bindings(hsdb->add_entry);
        sqlite3_reset(hsdb->add_entry);
        if(ret != SQLITE_DONE)
            goto rollback;

        sqlite3_bind_text(hsdb->add_principal, 1,
                          principal_string, -1, SQLITE_STATIC);
        ret = hdb_sqlite_step(context, hsdb->db, hsdb->add_principal);
        sqlite3_clear_bindings(hsdb->add_principal);
        sqlite3_reset(hsdb->add_principal);
        if(ret != SQLITE_DONE)
            goto rollback;

        entry_id = sqlite3_column_int64(get_ids, 1);

    } else if(ret == SQLITE_ROW) { /* Found a principal */

        if(! (flags & HDB_F_REPLACE)) /* Not allowed to replace it */
            goto rollback;

        entry_id = sqlite3_column_int64(get_ids, 1);

        sqlite3_bind_int64(hsdb->delete_aliases, 1, entry_id);
        ret = hdb_sqlite_step_once(context, db, hsdb->delete_aliases);
        if(ret != SQLITE_DONE)
            goto rollback;

        sqlite3_bind_blob(hsdb->update_entry, 1,
                          value.data, value.length, SQLITE_STATIC);
        sqlite3_bind_int64(hsdb->update_entry, 2, entry_id);
        ret = hdb_sqlite_step_once(context, db, hsdb->update_entry);
        if(ret != SQLITE_DONE)
            goto rollback;

    } else {
	/* Error! */
        goto rollback;
    }

    ret = hdb_entry_get_aliases(&entry->entry, &aliases);
    if(ret || aliases == NULL)
        goto commit;

    for(i = 0; i < aliases->aliases.len; i++) {

        ret = krb5_unparse_name(context, &aliases->aliases.val[i],
				&alias_string);
        if (ret) {
            free(alias_string);
            goto rollback;
        }

        sqlite3_bind_text(hsdb->add_alias, 1, alias_string,
                          -1, SQLITE_STATIC);
        sqlite3_bind_int64(hsdb->add_alias, 2, entry_id);
        ret = hdb_sqlite_step_once(context, db, hsdb->add_alias);

        free(alias_string);

        if(ret != SQLITE_DONE)
            goto rollback;
    }

    ret = 0;

commit:

    free(principal_string);

    krb5_data_free(&value);

    sqlite3_clear_bindings(get_ids);
    sqlite3_reset(get_ids);

    ret = hdb_sqlite_exec_stmt(context, hsdb->db, "COMMIT", EINVAL);
    if(ret != SQLITE_OK)
	krb5_warnx(context, "hdb-sqlite: COMMIT problem: %d: %s",
		   ret, sqlite3_errmsg(hsdb->db));

    return ret;

rollback:

    krb5_warnx(context, "hdb-sqlite: store rollback problem: %d: %s",
	       ret, sqlite3_errmsg(hsdb->db));

    free(principal_string);

    ret = hdb_sqlite_exec_stmt(context, hsdb->db,
                               "ROLLBACK", EINVAL);
    return ret;
}