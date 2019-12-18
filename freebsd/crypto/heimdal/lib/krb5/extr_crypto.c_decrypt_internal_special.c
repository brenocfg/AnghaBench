#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _krb5_encryption_type {size_t confoundersize; size_t padsize; scalar_t__ (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,int,void*) ;int /*<<< orphan*/  checksum; } ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_5__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  TYPE_2__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {int /*<<< orphan*/  key; struct _krb5_encryption_type* et; } ;

/* Variables and functions */
 size_t CHECKSUMSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KRB5_BAD_MSIZE ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,size_t) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * realloc (unsigned char*,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static krb5_error_code
decrypt_internal_special(krb5_context context,
			 krb5_crypto crypto,
			 int usage,
			 void *data,
			 size_t len,
			 krb5_data *result,
			 void *ivec)
{
    struct _krb5_encryption_type *et = crypto->et;
    size_t cksum_sz = CHECKSUMSIZE(et->checksum);
    size_t sz = len - cksum_sz - et->confoundersize;
    unsigned char *p;
    krb5_error_code ret;

    if ((len % et->padsize) != 0) {
	krb5_clear_error_message(context);
	return KRB5_BAD_MSIZE;
    }
    if (len < cksum_sz + et->confoundersize) {
	krb5_set_error_message(context, KRB5_BAD_MSIZE,
			       N_("Encrypted data shorter then "
				  "checksum + confunder", ""));
	return KRB5_BAD_MSIZE;
    }

    p = malloc (len);
    if (p == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    memcpy(p, data, len);

    ret = (*et->encrypt)(context, &crypto->key, p, len, FALSE, usage, ivec);
    if (ret) {
	free(p);
	return ret;
    }

    memmove (p, p + cksum_sz + et->confoundersize, sz);
    result->data = realloc(p, sz);
    if(result->data == NULL && sz != 0) {
	free(p);
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    result->length = sz;
    return 0;
}