#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct _krb5_checksum_type {scalar_t__ checksumsize; scalar_t__ (* checksum ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_8__*) ;int /*<<< orphan*/  type; } ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
struct TYPE_21__ {TYPE_3__ keyvalue; } ;
typedef  TYPE_5__ krb5_keyblock ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_22__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ krb5_data ;
typedef  TYPE_7__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_24__ {TYPE_6__ checksum; int /*<<< orphan*/  cksumtype; } ;
struct TYPE_17__ {int /*<<< orphan*/  key; } ;
struct TYPE_23__ {TYPE_4__* et; TYPE_1__ key; } ;
struct TYPE_20__ {scalar_t__ blocksize; TYPE_2__* keytype; int /*<<< orphan*/  type; struct _krb5_checksum_type* checksum; } ;
struct TYPE_18__ {int /*<<< orphan*/ * (* evp ) () ;} ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_8__ Checksum ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_Cipher (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  krb5_abortx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ krb5_data_alloc (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_6__*) ; 
 scalar_t__ krb5_derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_5__**) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/ * stub2 () ; 

__attribute__((used)) static krb5_error_code
AES_PRF(krb5_context context,
	krb5_crypto crypto,
	const krb5_data *in,
	krb5_data *out)
{
    struct _krb5_checksum_type *ct = crypto->et->checksum;
    krb5_error_code ret;
    Checksum result;
    krb5_keyblock *derived;

    result.cksumtype = ct->type;
    ret = krb5_data_alloc(&result.checksum, ct->checksumsize);
    if (ret) {
	krb5_set_error_message(context, ret, N_("malloc: out memory", ""));
	return ret;
    }

    ret = (*ct->checksum)(context, NULL, in->data, in->length, 0, &result);
    if (ret) {
	krb5_data_free(&result.checksum);
	return ret;
    }

    if (result.checksum.length < crypto->et->blocksize)
	krb5_abortx(context, "internal prf error");

    derived = NULL;
    ret = krb5_derive_key(context, crypto->key.key,
			  crypto->et->type, "prf", 3, &derived);
    if (ret)
	krb5_abortx(context, "krb5_derive_key");

    ret = krb5_data_alloc(out, crypto->et->blocksize);
    if (ret)
	krb5_abortx(context, "malloc failed");

    {
	const EVP_CIPHER *c = (*crypto->et->keytype->evp)();
	EVP_CIPHER_CTX *ctx;

	ctx = EVP_CIPHER_CTX_new(); /* ivec all zero */
	if (ctx == NULL)
	    krb5_abortx(context, "malloc failed");
	EVP_CipherInit_ex(ctx, c, NULL, derived->keyvalue.data, NULL, 1);
	EVP_Cipher(ctx, out->data, result.checksum.data,
		   crypto->et->blocksize);
	EVP_CIPHER_CTX_free(ctx);
    }

    krb5_data_free(&result.checksum);
    krb5_free_keyblock(context, derived);

    return ret;
}