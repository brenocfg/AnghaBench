#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_data {TYPE_3__* key; } ;
struct _krb5_checksum_type {int flags; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  TYPE_2__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_8__ {size_t length; scalar_t__ data; } ;
struct TYPE_10__ {TYPE_1__ keyvalue; } ;
struct TYPE_9__ {struct _krb5_key_data key; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int F_DERIVED ; 
 int F_VARIANT ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ _get_derived_key (int /*<<< orphan*/ ,TYPE_2__*,unsigned int,struct _krb5_key_data**) ; 
 scalar_t__ _key_schedule (int /*<<< orphan*/ ,struct _krb5_key_data*) ; 
 struct _krb5_key_data* _new_derived_key (TYPE_2__*,int) ; 
 scalar_t__ krb5_copy_keyblock (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__**) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
get_checksum_key(krb5_context context,
		 krb5_crypto crypto,
		 unsigned usage,  /* not krb5_key_usage */
		 struct _krb5_checksum_type *ct,
		 struct _krb5_key_data **key)
{
    krb5_error_code ret = 0;

    if(ct->flags & F_DERIVED)
	ret = _get_derived_key(context, crypto, usage, key);
    else if(ct->flags & F_VARIANT) {
	size_t i;

	*key = _new_derived_key(crypto, 0xff/* KRB5_KU_RFC1510_VARIANT */);
	if(*key == NULL) {
	    krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	    return ENOMEM;
	}
	ret = krb5_copy_keyblock(context, crypto->key.key, &(*key)->key);
	if(ret)
	    return ret;
	for(i = 0; i < (*key)->key->keyvalue.length; i++)
	    ((unsigned char*)(*key)->key->keyvalue.data)[i] ^= 0xF0;
    } else {
	*key = &crypto->key;
    }
    if(ret == 0)
	ret = _key_schedule(context, *key);
    return ret;
}