#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _krb5_key_type {int bits; int type; } ;
struct _krb5_key_data {int /*<<< orphan*/ * schedule; TYPE_2__* key; } ;
struct _krb5_encryption_type {int blocksize; int /*<<< orphan*/  (* encrypt ) (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;struct _krb5_key_type* keytype; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_3__ {unsigned char* data; unsigned int length; } ;
struct TYPE_4__ {TYPE_1__ keyvalue; } ;

/* Variables and functions */
#define  ENCTYPE_AES128_CTS_HMAC_SHA1_96 130 
#define  ENCTYPE_AES256_CTS_HMAC_SHA1_96 129 
 scalar_t__ ENOMEM ; 
#define  ETYPE_OLD_DES3_CBC_SHA1 128 
 scalar_t__ KRB5_CRYPTO_INTERNAL ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ _key_schedule (int /*<<< orphan*/ ,struct _krb5_key_data*) ; 
 int /*<<< orphan*/  _krb5_DES3_random_to_key (int /*<<< orphan*/ ,TYPE_2__*,unsigned char*,unsigned int) ; 
 scalar_t__ _krb5_n_fold (void*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  free_key_schedule (int /*<<< orphan*/ ,struct _krb5_key_data*,struct _krb5_encryption_type*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct _krb5_key_data*,unsigned char*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct _krb5_key_data*,void*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

krb5_error_code
_krb5_derive_key(krb5_context context,
		 struct _krb5_encryption_type *et,
		 struct _krb5_key_data *key,
		 const void *constant,
		 size_t len)
{
    unsigned char *k = NULL;
    unsigned int nblocks = 0, i;
    krb5_error_code ret = 0;
    struct _krb5_key_type *kt = et->keytype;

    ret = _key_schedule(context, key);
    if(ret)
	return ret;
    if(et->blocksize * 8 < kt->bits || len != et->blocksize) {
	nblocks = (kt->bits + et->blocksize * 8 - 1) / (et->blocksize * 8);
	k = malloc(nblocks * et->blocksize);
	if(k == NULL) {
	    ret = ENOMEM;
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}
	ret = _krb5_n_fold(constant, len, k, et->blocksize);
	if (ret) {
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}

	for(i = 0; i < nblocks; i++) {
	    if(i > 0)
		memcpy(k + i * et->blocksize,
		       k + (i - 1) * et->blocksize,
		       et->blocksize);
	    (*et->encrypt)(context, key, k + i * et->blocksize, et->blocksize,
			   1, 0, NULL);
	}
    } else {
	/* this case is probably broken, but won't be run anyway */
	void *c = malloc(len);
	size_t res_len = (kt->bits + 7) / 8;

	if(len != 0 && c == NULL) {
	    ret = ENOMEM;
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}
	memcpy(c, constant, len);
	(*et->encrypt)(context, key, c, len, 1, 0, NULL);
	k = malloc(res_len);
	if(res_len != 0 && k == NULL) {
	    free(c);
	    ret = ENOMEM;
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}
	ret = _krb5_n_fold(c, len, k, res_len);
	free(c);
	if (ret) {
	    krb5_set_error_message(context, ret, N_("malloc: out of memory", ""));
	    goto out;
	}
    }

    /* XXX keytype dependent post-processing */
    switch(kt->type) {
    case ETYPE_OLD_DES3_CBC_SHA1:
	_krb5_DES3_random_to_key(context, key->key, k, nblocks * et->blocksize);
	break;
    case ENCTYPE_AES128_CTS_HMAC_SHA1_96:
    case ENCTYPE_AES256_CTS_HMAC_SHA1_96:
	memcpy(key->key->keyvalue.data, k, key->key->keyvalue.length);
	break;
    default:
	ret = KRB5_CRYPTO_INTERNAL;
	krb5_set_error_message(context, ret,
			       N_("derive_key() called with unknown keytype (%u)", ""),
			       kt->type);
	break;
    }
 out:
    if (key->schedule) {
	free_key_schedule(context, key, et);
	key->schedule = NULL;
    }
    if (k) {
	memset(k, 0, nblocks * et->blocksize);
	free(k);
    }
    return ret;
}