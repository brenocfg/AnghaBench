#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int SSL_CTX_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_USE_PRIVATEKEY_ASN1 ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_PrivateKey (int,int /*<<< orphan*/ *,unsigned char const**,long) ; 

int SSL_CTX_use_PrivateKey_ASN1(int type, SSL_CTX *ctx,
                                const unsigned char *d, long len)
{
    int ret;
    const unsigned char *p;
    EVP_PKEY *pkey;

    p = d;
    if ((pkey = d2i_PrivateKey(type, NULL, &p, (long)len)) == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_PRIVATEKEY_ASN1, ERR_R_ASN1_LIB);
        return 0;
    }

    ret = SSL_CTX_use_PrivateKey(ctx, pkey);
    EVP_PKEY_free(pkey);
    return ret;
}