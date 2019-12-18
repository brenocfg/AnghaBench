#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ krb5_error_code ;
struct TYPE_14__ {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;
typedef  TYPE_3__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_4__* hdb_master_key ;
struct TYPE_12__ {TYPE_3__ keyvalue; } ;
struct TYPE_16__ {int /*<<< orphan*/ * mkvno; TYPE_1__ key; } ;
struct TYPE_13__ {int /*<<< orphan*/  vno; } ;
struct TYPE_15__ {TYPE_2__ keytab; } ;
typedef  TYPE_5__ Key ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ HDB_ERR_NO_MKEY ; 
 int /*<<< orphan*/  HDB_KU_MKEY ; 
 TYPE_4__* _hdb_find_master_key (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ _hdb_mkey_encrypt (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

krb5_error_code
hdb_seal_key_mkey(krb5_context context, Key *k, hdb_master_key mkey)
{
    krb5_error_code ret;
    krb5_data res;
    hdb_master_key key;

    if(k->mkvno != NULL)
	return 0;

    key = _hdb_find_master_key(k->mkvno, mkey);

    if (key == NULL)
	return HDB_ERR_NO_MKEY;

    ret = _hdb_mkey_encrypt(context, key, HDB_KU_MKEY,
			    k->key.keyvalue.data,
			    k->key.keyvalue.length,
			    &res);
    if (ret)
	return ret;

    memset(k->key.keyvalue.data, 0, k->key.keyvalue.length);
    free(k->key.keyvalue.data);
    k->key.keyvalue = res;

    if (k->mkvno == NULL) {
	k->mkvno = malloc(sizeof(*k->mkvno));
	if (k->mkvno == NULL)
	    return ENOMEM;
    }
    *k->mkvno = key->keytab.vno;

    return 0;
}