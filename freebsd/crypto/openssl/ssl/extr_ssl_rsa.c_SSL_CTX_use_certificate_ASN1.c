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
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int SSL_CTX_use_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_USE_CERTIFICATE_ASN1 ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,unsigned char const**,long) ; 

int SSL_CTX_use_certificate_ASN1(SSL_CTX *ctx, int len, const unsigned char *d)
{
    X509 *x;
    int ret;

    x = d2i_X509(NULL, &d, (long)len);
    if (x == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_ASN1, ERR_R_ASN1_LIB);
        return 0;
    }

    ret = SSL_CTX_use_certificate(ctx, x);
    X509_free(x);
    return ret;
}