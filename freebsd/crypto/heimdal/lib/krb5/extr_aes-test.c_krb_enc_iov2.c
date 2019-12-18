#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* data; size_t length; } ;
typedef  TYPE_2__ krb5_data ;
struct TYPE_9__ {size_t length; char* data; } ;
struct TYPE_11__ {TYPE_1__ data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ krb5_crypto_iov ;
typedef  int /*<<< orphan*/  krb5_crypto ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  iov ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_DATA ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_EMPTY ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_HEADER ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_PADDING ; 
 int /*<<< orphan*/  KRB5_CRYPTO_TYPE_TRAILER ; 
 void* emalloc (size_t) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_crypto_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_2__*) ; 
 int krb5_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,char*,size_t,TYPE_2__*) ; 
 int krb5_decrypt_iov_ivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int krb5_encrypt_iov_ivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,int,char*,...) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static int
krb_enc_iov2(krb5_context context,
	     krb5_crypto crypto,
	     unsigned usage,
	     size_t cipher_len,
	     krb5_data *clear)
{
    krb5_crypto_iov iov[4];
    krb5_data decrypt;
    int ret;
    char *p, *q;
    size_t len, i;

    p = clear->data;
    len = clear->length;

    iov[0].flags = KRB5_CRYPTO_TYPE_HEADER;
    krb5_crypto_length(context, crypto, iov[0].flags, &iov[0].data.length);
    iov[0].data.data = emalloc(iov[0].data.length);

    iov[1].flags = KRB5_CRYPTO_TYPE_DATA;
    iov[1].data.length = len;
    iov[1].data.data = emalloc(iov[1].data.length);
    memcpy(iov[1].data.data, p, iov[1].data.length);

    /* padding buffer */
    iov[2].flags = KRB5_CRYPTO_TYPE_PADDING;
    krb5_crypto_length(context, crypto, KRB5_CRYPTO_TYPE_PADDING, &iov[2].data.length);
    iov[2].data.data = emalloc(iov[2].data.length);

    iov[3].flags = KRB5_CRYPTO_TYPE_TRAILER;
    krb5_crypto_length(context, crypto, iov[3].flags, &iov[3].data.length);
    iov[3].data.data = emalloc(iov[3].data.length);

    ret = krb5_encrypt_iov_ivec(context, crypto, usage,
				iov, sizeof(iov)/sizeof(iov[0]), NULL);
    if (ret)
	errx(1, "encrypt iov failed: %d", ret);

    /* check len */
    for (i = 0, len = 0; i < sizeof(iov)/sizeof(iov[0]); i++)
	len += iov[i].data.length;
    if (len != cipher_len)
	errx(1, "cipher len wrong");

    /*
     * Plain decrypt
     */

    p = q = emalloc(len);
    for (i = 0; i < sizeof(iov)/sizeof(iov[0]); i++) {
	memcpy(q, iov[i].data.data, iov[i].data.length);
	q += iov[i].data.length;
    }

    ret = krb5_decrypt(context, crypto, usage, p, len, &decrypt);
    if (ret)
	krb5_err(context, 1, ret, "krb5_decrypt");
    else
	krb5_data_free(&decrypt);

    free(p);

    /*
     * Now decrypt use iov
     */

    /* padding turn into data */
    p = q = emalloc(iov[1].data.length + iov[2].data.length);

    memcpy(q, iov[1].data.data, iov[1].data.length);
    q += iov[1].data.length;
    memcpy(q, iov[2].data.data, iov[2].data.length);

    free(iov[1].data.data);
    free(iov[2].data.data);

    iov[1].data.data = p;
    iov[1].data.length += iov[2].data.length;

    iov[2].flags = KRB5_CRYPTO_TYPE_EMPTY;
    iov[2].data.length = 0;

    ret = krb5_decrypt_iov_ivec(context, crypto, usage,
				iov, sizeof(iov)/sizeof(iov[0]), NULL);
    free(iov[0].data.data);
    free(iov[3].data.data);

    if (ret)
	krb5_err(context, 1, ret, "decrypt iov failed: %d", ret);

    if (clear->length != iov[1].data.length)
	errx(1, "length incorrect");

    p = clear->data;
    if (memcmp(iov[1].data.data, p, iov[1].data.length) != 0)
	errx(1, "iov[1] incorrect");

    free(iov[1].data.data);

    return 0;
}