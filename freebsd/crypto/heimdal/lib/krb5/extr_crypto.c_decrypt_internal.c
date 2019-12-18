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
struct _krb5_encryption_type {size_t padsize; size_t confoundersize; int /*<<< orphan*/  checksum; scalar_t__ (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_8__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  TYPE_2__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_10__ {int /*<<< orphan*/  cksumtype; int /*<<< orphan*/  checksum; } ;
struct TYPE_9__ {int /*<<< orphan*/  key; struct _krb5_encryption_type* et; } ;
typedef  TYPE_3__ Checksum ;

/* Variables and functions */
 size_t CHECKSUMSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECKSUMTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ KRB5_BAD_MSIZE ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 scalar_t__ _key_schedule (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  free_Checksum (TYPE_3__*) ; 
 int /*<<< orphan*/  krb5_clear_error_message (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_data_copy (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,size_t) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * realloc (unsigned char*,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ verify_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t,TYPE_3__*) ; 

__attribute__((used)) static krb5_error_code
decrypt_internal(krb5_context context,
		 krb5_crypto crypto,
		 void *data,
		 size_t len,
		 krb5_data *result,
		 void *ivec)
{
    krb5_error_code ret;
    unsigned char *p;
    Checksum cksum;
    size_t checksum_sz, l;
    struct _krb5_encryption_type *et = crypto->et;

    if ((len % et->padsize) != 0) {
	krb5_clear_error_message(context);
	return KRB5_BAD_MSIZE;
    }
    checksum_sz = CHECKSUMSIZE(et->checksum);
    if (len < checksum_sz + et->confoundersize) {
	krb5_set_error_message(context, KRB5_BAD_MSIZE,
			       N_("Encrypted data shorter then "
				  "checksum + confunder", ""));
	return KRB5_BAD_MSIZE;
    }

    p = malloc(len);
    if(len != 0 && p == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    memcpy(p, data, len);

    ret = _key_schedule(context, &crypto->key);
    if(ret) {
	free(p);
	return ret;
    }
    ret = (*et->encrypt)(context, &crypto->key, p, len, 0, 0, ivec);
    if (ret) {
	free(p);
	return ret;
    }
    ret = krb5_data_copy(&cksum.checksum, p + et->confoundersize, checksum_sz);
    if(ret) {
 	free(p);
 	return ret;
    }
    memset(p + et->confoundersize, 0, checksum_sz);
    cksum.cksumtype = CHECKSUMTYPE(et->checksum);
    ret = verify_checksum(context, NULL, 0, p, len, &cksum);
    free_Checksum(&cksum);
    if(ret) {
	free(p);
	return ret;
    }
    l = len - et->confoundersize - checksum_sz;
    memmove(p, p + et->confoundersize + checksum_sz, l);
    result->data = realloc(p, l);
    if(result->data == NULL && l != 0) {
	free(p);
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    result->length = l;
    return 0;
}