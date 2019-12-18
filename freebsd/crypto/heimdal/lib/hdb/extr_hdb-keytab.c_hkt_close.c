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
typedef  TYPE_1__* hdb_keytab ;
struct TYPE_5__ {int /*<<< orphan*/  hdb_db; } ;
struct TYPE_4__ {int /*<<< orphan*/ * keytab; } ;
typedef  TYPE_2__ HDB ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
hkt_close(krb5_context context, HDB *db)
{
    hdb_keytab k = (hdb_keytab)db->hdb_db;
    krb5_error_code ret;

    assert(k->keytab);

    ret = krb5_kt_close(context, k->keytab);
    k->keytab = NULL;

    return ret;
}