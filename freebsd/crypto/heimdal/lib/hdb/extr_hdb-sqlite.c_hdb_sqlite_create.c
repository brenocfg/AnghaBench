#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_7__ {int /*<<< orphan*/ * hdb__del; int /*<<< orphan*/ * hdb__put; int /*<<< orphan*/ * hdb__get; int /*<<< orphan*/  hdb_rename; int /*<<< orphan*/  hdb_destroy; int /*<<< orphan*/  hdb_remove; int /*<<< orphan*/  hdb_store; int /*<<< orphan*/  hdb_fetch_kvno; int /*<<< orphan*/  hdb_nextkey; int /*<<< orphan*/  hdb_firstkey; int /*<<< orphan*/  hdb_unlock; int /*<<< orphan*/  hdb_lock; int /*<<< orphan*/  hdb_close; int /*<<< orphan*/  hdb_open; scalar_t__ hdb_capability_flags; scalar_t__ hdb_openp; scalar_t__ hdb_master_key_set; struct TYPE_7__* hdb_db; } ;
typedef  TYPE_1__ hdb_sqlite_db ;
typedef  TYPE_1__ HDB ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hdb_sqlite_close ; 
 int /*<<< orphan*/  hdb_sqlite_destroy ; 
 int /*<<< orphan*/  hdb_sqlite_fetch_kvno ; 
 int /*<<< orphan*/  hdb_sqlite_firstkey ; 
 int /*<<< orphan*/  hdb_sqlite_lock ; 
 scalar_t__ hdb_sqlite_make_database (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  hdb_sqlite_nextkey ; 
 int /*<<< orphan*/  hdb_sqlite_open ; 
 int /*<<< orphan*/  hdb_sqlite_remove ; 
 int /*<<< orphan*/  hdb_sqlite_rename ; 
 int /*<<< orphan*/  hdb_sqlite_store ; 
 int /*<<< orphan*/  hdb_sqlite_unlock ; 
 scalar_t__ krb5_enomem (int /*<<< orphan*/ ) ; 

krb5_error_code
hdb_sqlite_create(krb5_context context, HDB **db, const char *argument)
{
    krb5_error_code ret;
    hdb_sqlite_db *hsdb;

    *db = calloc(1, sizeof (**db));
    if (*db == NULL)
	return krb5_enomem(context);

    hsdb = (hdb_sqlite_db*) calloc(1, sizeof (*hsdb));
    if (hsdb == NULL) {
        free(*db);
        *db = NULL;
	return krb5_enomem(context);
    }

    (*db)->hdb_db = hsdb;

    /* XXX make_database should make sure everything else is freed on error */
    ret = hdb_sqlite_make_database(context, *db, argument);
    if (ret) {
        free((*db)->hdb_db);
        free(*db);

        return ret;
    }

    (*db)->hdb_master_key_set = 0;
    (*db)->hdb_openp = 0;
    (*db)->hdb_capability_flags = 0;

    (*db)->hdb_open = hdb_sqlite_open;
    (*db)->hdb_close = hdb_sqlite_close;

    (*db)->hdb_lock = hdb_sqlite_lock;
    (*db)->hdb_unlock = hdb_sqlite_unlock;
    (*db)->hdb_firstkey = hdb_sqlite_firstkey;
    (*db)->hdb_nextkey = hdb_sqlite_nextkey;
    (*db)->hdb_fetch_kvno = hdb_sqlite_fetch_kvno;
    (*db)->hdb_store = hdb_sqlite_store;
    (*db)->hdb_remove = hdb_sqlite_remove;
    (*db)->hdb_destroy = hdb_sqlite_destroy;
    (*db)->hdb_rename = hdb_sqlite_rename;
    (*db)->hdb__get = NULL;
    (*db)->hdb__put = NULL;
    (*db)->hdb__del = NULL;

    return 0;
}