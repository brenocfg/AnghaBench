#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct _krb5_key_data {TYPE_6__* key; int /*<<< orphan*/ * schedule; } ;
struct _krb5_encryption_type {TYPE_2__* keytype; } ;
struct TYPE_11__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_1__ saltvalue; } ;
typedef  TYPE_3__ krb5_salt ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
struct TYPE_14__ {int length; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
struct TYPE_16__ {TYPE_5__ keyvalue; int /*<<< orphan*/  keytype; } ;
struct TYPE_12__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC (TYPE_6__*,int) ; 
 int ENOMEM ; 
 int KRB5_PROG_KEYTYPE_NOSUPP ; 
 char* N_ (char*,char*) ; 
 int PKCS5_PBKDF2_HMAC_SHA1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _krb5_AES_string_to_default_iterator ; 
 int _krb5_derive_key (int /*<<< orphan*/ ,struct _krb5_encryption_type*,struct _krb5_key_data*,char*,int /*<<< orphan*/ ) ; 
 struct _krb5_encryption_type* _krb5_find_enctype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _krb5_free_key_data (int /*<<< orphan*/ ,struct _krb5_key_data*,struct _krb5_encryption_type*) ; 
 int /*<<< orphan*/  _krb5_get_int (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int krb5_copy_keyblock_contents (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int krb5_data_alloc (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static krb5_error_code
AES_string_to_key(krb5_context context,
		  krb5_enctype enctype,
		  krb5_data password,
		  krb5_salt salt,
		  krb5_data opaque,
		  krb5_keyblock *key)
{
    krb5_error_code ret;
    uint32_t iter;
    struct _krb5_encryption_type *et;
    struct _krb5_key_data kd;

    if (opaque.length == 0)
	iter = _krb5_AES_string_to_default_iterator;
    else if (opaque.length == 4) {
	unsigned long v;
	_krb5_get_int(opaque.data, &v, 4);
	iter = ((uint32_t)v);
    } else
	return KRB5_PROG_KEYTYPE_NOSUPP; /* XXX */

    et = _krb5_find_enctype(enctype);
    if (et == NULL)
	return KRB5_PROG_KEYTYPE_NOSUPP;

    kd.schedule = NULL;
    ALLOC(kd.key, 1);
    if(kd.key == NULL) {
	krb5_set_error_message (context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    kd.key->keytype = enctype;
    ret = krb5_data_alloc(&kd.key->keyvalue, et->keytype->size);
    if (ret) {
	krb5_set_error_message (context, ret, N_("malloc: out of memory", ""));
	return ret;
    }

    ret = PKCS5_PBKDF2_HMAC_SHA1(password.data, password.length,
				 salt.saltvalue.data, salt.saltvalue.length,
				 iter,
				 et->keytype->size, kd.key->keyvalue.data);
    if (ret != 1) {
	_krb5_free_key_data(context, &kd, et);
	krb5_set_error_message(context, KRB5_PROG_KEYTYPE_NOSUPP,
			       "Error calculating s2k");
	return KRB5_PROG_KEYTYPE_NOSUPP;
    }

    ret = _krb5_derive_key(context, et, &kd, "kerberos", strlen("kerberos"));
    if (ret == 0)
	ret = krb5_copy_keyblock_contents(context, kd.key, key);
    _krb5_free_key_data(context, &kd, et);

    return ret;
}