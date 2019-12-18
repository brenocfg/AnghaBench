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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int SQLITE_BUSY ; 
 int SQLITE_IOERR_BLOCKED ; 
 int SQLITE_LOCKED ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hdb_sqlite_step(krb5_context context, sqlite3 *db, sqlite3_stmt *stmt)
{
    int ret;

    ret = sqlite3_step(stmt);
    while(((ret == SQLITE_BUSY) ||
           (ret == SQLITE_IOERR_BLOCKED) ||
           (ret == SQLITE_LOCKED))) {
	krb5_warnx(context, "hdb-sqlite: step busy: %d", (int)getpid());
        sleep(1);
        ret = sqlite3_step(stmt);
    }
    return ret;
}