#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  MAX_RETRIES ; 
 int SQLITE_BUSY ; 
 int SQLITE_IOERR_BLOCKED ; 
 int SQLITE_LOCKED ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hdb_sqlite_prepare_stmt(krb5_context context,
                        sqlite3 *db,
                        sqlite3_stmt **statement,
                        const char *str)
{
    int ret, tries = 0;

    ret = sqlite3_prepare_v2(db, str, -1, statement, NULL);
    while((tries++ < MAX_RETRIES) &&
	  ((ret == SQLITE_BUSY) ||
           (ret == SQLITE_IOERR_BLOCKED) ||
           (ret == SQLITE_LOCKED))) {
	krb5_warnx(context, "hdb-sqlite: prepare busy");
        sleep(1);
        ret = sqlite3_prepare_v2(db, str, -1, statement, NULL);
    }

    if (ret != SQLITE_OK) {
        krb5_set_error_message(context, EINVAL,
			       "Failed to prepare stmt %s: %s",
			       str, sqlite3_errmsg(db));
        return EINVAL;
    }

    return 0;
}