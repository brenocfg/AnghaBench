#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct _krb5_encryption_type {size_t confoundersize; size_t padsize; scalar_t__ (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  checksum; } ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_11__ {unsigned char* data; size_t length; } ;
typedef  TYPE_2__ krb5_data ;
typedef  TYPE_3__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_10__ {size_t length; void const* data; } ;
struct TYPE_13__ {TYPE_1__ checksum; } ;
struct TYPE_12__ {int /*<<< orphan*/  key; struct _krb5_encryption_type* et; } ;
typedef  TYPE_4__ Checksum ;

/* Variables and functions */
 size_t CHECKSUMSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ KRB5_CRYPTO_INTERNAL ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ _key_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char* calloc (int,size_t) ; 
 scalar_t__ create_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,unsigned char*,size_t,TYPE_4__*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  free_Checksum (TYPE_4__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_generate_random_block (unsigned char*,size_t) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static krb5_error_code
encrypt_internal(krb5_context context,
		 krb5_crypto crypto,
		 const void *data,
		 size_t len,
		 krb5_data *result,
		 void *ivec)
{
    size_t sz, block_sz, checksum_sz;
    Checksum cksum;
    unsigned char *p, *q;
    krb5_error_code ret;
    const struct _krb5_encryption_type *et = crypto->et;

    checksum_sz = CHECKSUMSIZE(et->checksum);

    sz = et->confoundersize + checksum_sz + len;
    block_sz = (sz + et->padsize - 1) &~ (et->padsize - 1); /* pad */
    p = calloc(1, block_sz);
    if(p == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    q = p;
    krb5_generate_random_block(q, et->confoundersize); /* XXX */
    q += et->confoundersize;
    memset(q, 0, checksum_sz);
    q += checksum_sz;
    memcpy(q, data, len);

    ret = create_checksum(context,
			  et->checksum,
			  crypto,
			  0,
			  p,
			  block_sz,
			  &cksum);
    if(ret == 0 && cksum.checksum.length != checksum_sz) {
	krb5_clear_error_message (context);
	free_Checksum(&cksum);
	ret = KRB5_CRYPTO_INTERNAL;
    }
    if(ret)
	goto fail;
    memcpy(p + et->confoundersize, cksum.checksum.data, cksum.checksum.length);
    free_Checksum(&cksum);
    ret = _key_schedule(context, &crypto->key);
    if(ret)
	goto fail;
    ret = (*et->encrypt)(context, &crypto->key, p, block_sz, 1, 0, ivec);
    if (ret) {
	memset(p, 0, block_sz);
	free(p);
	return ret;
    }
    result->data = p;
    result->length = block_sz;
    return 0;
 fail:
    memset(p, 0, block_sz);
    free(p);
    return ret;
}