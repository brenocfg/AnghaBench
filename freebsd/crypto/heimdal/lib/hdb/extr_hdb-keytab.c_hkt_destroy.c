#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* hdb_keytab ;
struct TYPE_6__ {struct TYPE_6__* hdb_name; struct TYPE_6__* path; int /*<<< orphan*/  hdb_db; } ;
typedef  TYPE_1__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hdb_clear_master_key (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static krb5_error_code
hkt_destroy(krb5_context context, HDB *db)
{
    hdb_keytab k = (hdb_keytab)db->hdb_db;
    krb5_error_code ret;

    ret = hdb_clear_master_key (context, db);

    free(k->path);
    free(k);

    free(db->hdb_name);
    free(db);
    return ret;
}