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
struct _krb5_encryption_type {size_t confoundersize; scalar_t__ (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,int,void*) ;int /*<<< orphan*/  checksum; } ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_5__ {char* data; size_t length; } ;
typedef  TYPE_1__ krb5_data ;
typedef  TYPE_2__* krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_6__ {int /*<<< orphan*/  key; struct _krb5_encryption_type* et; } ;

/* Variables and functions */
 size_t CHECKSUMSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_generate_random_block (char*,size_t) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ ,int,void*) ; 

__attribute__((used)) static krb5_error_code
encrypt_internal_special(krb5_context context,
			 krb5_crypto crypto,
			 int usage,
			 const void *data,
			 size_t len,
			 krb5_data *result,
			 void *ivec)
{
    struct _krb5_encryption_type *et = crypto->et;
    size_t cksum_sz = CHECKSUMSIZE(et->checksum);
    size_t sz = len + cksum_sz + et->confoundersize;
    char *tmp, *p;
    krb5_error_code ret;

    tmp = malloc (sz);
    if (tmp == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }
    p = tmp;
    memset (p, 0, cksum_sz);
    p += cksum_sz;
    krb5_generate_random_block(p, et->confoundersize);
    p += et->confoundersize;
    memcpy (p, data, len);
    ret = (*et->encrypt)(context, &crypto->key, tmp, sz, TRUE, usage, ivec);
    if (ret) {
	memset(tmp, 0, sz);
	free(tmp);
	return ret;
    }
    result->data   = tmp;
    result->length = sz;
    return 0;
}