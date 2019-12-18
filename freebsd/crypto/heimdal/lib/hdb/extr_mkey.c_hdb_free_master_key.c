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
struct hdb_master_key_data {struct hdb_master_key_data* next; scalar_t__ crypto; int /*<<< orphan*/  keytab; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  struct hdb_master_key_data* hdb_master_key ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct hdb_master_key_data*) ; 
 int /*<<< orphan*/  krb5_crypto_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_kt_free_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
hdb_free_master_key(krb5_context context, hdb_master_key mkey)
{
    struct hdb_master_key_data *ptr;
    while(mkey) {
	krb5_kt_free_entry(context, &mkey->keytab);
	if (mkey->crypto)
	    krb5_crypto_destroy(context, mkey->crypto);
	ptr = mkey;
	mkey = mkey->next;
	free(ptr);
    }
}