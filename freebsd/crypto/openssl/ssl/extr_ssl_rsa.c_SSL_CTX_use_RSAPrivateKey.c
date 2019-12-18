#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ SSL_CTX ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 scalar_t__ EVP_PKEY_assign_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_CTX_USE_RSAPRIVATEKEY ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_set_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int SSL_CTX_use_RSAPrivateKey(SSL_CTX *ctx, RSA *rsa)
{
    int ret;
    EVP_PKEY *pkey;

    if (rsa == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if ((pkey = EVP_PKEY_new()) == NULL) {
        SSLerr(SSL_F_SSL_CTX_USE_RSAPRIVATEKEY, ERR_R_EVP_LIB);
        return 0;
    }

    RSA_up_ref(rsa);
    if (EVP_PKEY_assign_RSA(pkey, rsa) <= 0) {
        RSA_free(rsa);
        EVP_PKEY_free(pkey);
        return 0;
    }

    ret = ssl_set_pkey(ctx->cert, pkey);
    EVP_PKEY_free(pkey);
    return ret;
}