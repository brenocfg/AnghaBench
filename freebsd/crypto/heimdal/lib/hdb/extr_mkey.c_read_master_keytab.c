#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_kt_cursor ;
struct TYPE_6__ {int /*<<< orphan*/  keyblock; } ;
typedef  TYPE_1__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_2__* hdb_master_key ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  crypto; TYPE_1__ keytab; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 TYPE_2__* calloc (int,int) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_kt_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_next_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_start_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
read_master_keytab(krb5_context context, const char *filename,
		   hdb_master_key *mkey)
{
    krb5_error_code ret;
    krb5_keytab id;
    krb5_kt_cursor cursor;
    krb5_keytab_entry entry;
    hdb_master_key p;

    ret = krb5_kt_resolve(context, filename, &id);
    if(ret)
	return ret;

    ret = krb5_kt_start_seq_get(context, id, &cursor);
    if(ret)
	goto out;
    *mkey = NULL;
    while(krb5_kt_next_entry(context, id, &entry, &cursor) == 0) {
	p = calloc(1, sizeof(*p));
	if(p == NULL) {
	    krb5_kt_end_seq_get(context, id, &cursor);
	    ret = ENOMEM;
	    goto out;
	}
	p->keytab = entry;
	ret = krb5_crypto_init(context, &p->keytab.keyblock, 0, &p->crypto);
	p->next = *mkey;
	*mkey = p;
    }
    krb5_kt_end_seq_get(context, id, &cursor);
  out:
    krb5_kt_close(context, id);
    return ret;
}