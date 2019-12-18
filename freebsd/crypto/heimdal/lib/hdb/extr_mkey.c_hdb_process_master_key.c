#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_2__* hdb_master_key ;
struct TYPE_9__ {scalar_t__ keytype; } ;
struct TYPE_7__ {int vno; int /*<<< orphan*/  timestamp; TYPE_3__ keyblock; int /*<<< orphan*/  principal; } ;
struct TYPE_8__ {int /*<<< orphan*/  crypto; TYPE_1__ keytab; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  hdb_free_master_key (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ krb5_copy_keyblock_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ krb5_crypto_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

krb5_error_code
hdb_process_master_key(krb5_context context,
		       int kvno, krb5_keyblock *key, krb5_enctype etype,
		       hdb_master_key *mkey)
{
    krb5_error_code ret;

    *mkey = calloc(1, sizeof(**mkey));
    if(*mkey == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }
    (*mkey)->keytab.vno = kvno;
    ret = krb5_parse_name(context, "K/M", &(*mkey)->keytab.principal);
    if(ret)
	goto fail;
    ret = krb5_copy_keyblock_contents(context, key, &(*mkey)->keytab.keyblock);
    if(ret)
	goto fail;
    if(etype != 0)
	(*mkey)->keytab.keyblock.keytype = etype;
    (*mkey)->keytab.timestamp = time(NULL);
    ret = krb5_crypto_init(context, key, etype, &(*mkey)->crypto);
    if(ret)
	goto fail;
    return 0;
 fail:
    hdb_free_master_key(context, *mkey);
    *mkey = NULL;
    return ret;
}