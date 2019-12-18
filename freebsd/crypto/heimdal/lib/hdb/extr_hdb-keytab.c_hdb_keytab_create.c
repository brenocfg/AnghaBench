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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* hdb_keytab ;
struct TYPE_7__ {int /*<<< orphan*/  hdb_destroy; int /*<<< orphan*/ * hdb__del; int /*<<< orphan*/ * hdb__put; int /*<<< orphan*/ * hdb__get; int /*<<< orphan*/ * hdb_rename; int /*<<< orphan*/  hdb_unlock; int /*<<< orphan*/  hdb_lock; int /*<<< orphan*/  hdb_nextkey; int /*<<< orphan*/  hdb_firstkey; int /*<<< orphan*/ * hdb_remove; int /*<<< orphan*/  hdb_store; int /*<<< orphan*/  hdb_fetch_kvno; int /*<<< orphan*/  hdb_close; int /*<<< orphan*/  hdb_open; scalar_t__ hdb_openp; scalar_t__ hdb_master_key_set; struct TYPE_7__* hdb_db; int /*<<< orphan*/ * path; } ;
typedef  TYPE_1__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hkt_close ; 
 int /*<<< orphan*/  hkt_destroy ; 
 int /*<<< orphan*/  hkt_fetch_kvno ; 
 int /*<<< orphan*/  hkt_firstkey ; 
 int /*<<< orphan*/  hkt_lock ; 
 int /*<<< orphan*/  hkt_nextkey ; 
 int /*<<< orphan*/  hkt_open ; 
 int /*<<< orphan*/  hkt_store ; 
 int /*<<< orphan*/  hkt_unlock ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

krb5_error_code
hdb_keytab_create(krb5_context context, HDB ** db, const char *arg)
{
    hdb_keytab k;

    *db = calloc(1, sizeof(**db));
    if (*db == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    memset(*db, 0, sizeof(**db));

    k = calloc(1, sizeof(*k));
    if (k == NULL) {
	free(*db);
	*db = NULL;
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }

    k->path = strdup(arg);
    if (k->path == NULL) {
	free(k);
	free(*db);
	*db = NULL;
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }


    (*db)->hdb_db = k;

    (*db)->hdb_master_key_set = 0;
    (*db)->hdb_openp = 0;
    (*db)->hdb_open = hkt_open;
    (*db)->hdb_close = hkt_close;
    (*db)->hdb_fetch_kvno = hkt_fetch_kvno;
    (*db)->hdb_store = hkt_store;
    (*db)->hdb_remove = NULL;
    (*db)->hdb_firstkey = hkt_firstkey;
    (*db)->hdb_nextkey = hkt_nextkey;
    (*db)->hdb_lock = hkt_lock;
    (*db)->hdb_unlock = hkt_unlock;
    (*db)->hdb_rename = NULL;
    (*db)->hdb__get = NULL;
    (*db)->hdb__put = NULL;
    (*db)->hdb__del = NULL;
    (*db)->hdb_destroy = hkt_destroy;

    return 0;
}