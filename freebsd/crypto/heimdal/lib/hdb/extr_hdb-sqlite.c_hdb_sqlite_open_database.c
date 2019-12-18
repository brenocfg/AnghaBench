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
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  db_file; } ;
typedef  TYPE_1__ hdb_sqlite_db ;
struct TYPE_5__ {scalar_t__ hdb_db; } ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int ENOENT ; 
 int SQLITE_OPEN_READWRITE ; 
 int krb5_enomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_open_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_open_database(krb5_context context, HDB *db, int flags)
{
    int ret;
    hdb_sqlite_db *hsdb = (hdb_sqlite_db*) db->hdb_db;

    ret = sqlite3_open_v2(hsdb->db_file, &hsdb->db,
                          SQLITE_OPEN_READWRITE | flags, NULL);

    if (ret) {
        if (hsdb->db) {
	    ret = ENOENT;
            krb5_set_error_message(context, ret,
                                  "Error opening sqlite database %s: %s",
                                  hsdb->db_file, sqlite3_errmsg(hsdb->db));
            sqlite3_close(hsdb->db);
            hsdb->db = NULL;
        } else
	    ret = krb5_enomem(context);
        return ret;
    }

    return 0;
}