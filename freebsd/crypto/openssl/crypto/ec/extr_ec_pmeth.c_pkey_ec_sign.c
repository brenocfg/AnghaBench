#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * md; } ;
struct TYPE_8__ {TYPE_2__* pkey; TYPE_4__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_7__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  TYPE_4__ EC_PKEY_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int ECDSA_sign (int,unsigned char const*,size_t,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 int ECDSA_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_PKEY_EC_SIGN ; 
 int /*<<< orphan*/  EC_R_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_MD_type (int /*<<< orphan*/ *) ; 
 int NID_sha1 ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

__attribute__((used)) static int pkey_ec_sign(EVP_PKEY_CTX *ctx, unsigned char *sig, size_t *siglen,
                        const unsigned char *tbs, size_t tbslen)
{
    int ret, type;
    unsigned int sltmp;
    EC_PKEY_CTX *dctx = ctx->data;
    EC_KEY *ec = ctx->pkey->pkey.ec;
    const int sig_sz = ECDSA_size(ec);

    /* ensure cast to size_t is safe */
    if (!ossl_assert(sig_sz > 0))
        return 0;

    if (sig == NULL) {
        *siglen = (size_t)sig_sz;
        return 1;
    }

    if (*siglen < (size_t)sig_sz) {
        ECerr(EC_F_PKEY_EC_SIGN, EC_R_BUFFER_TOO_SMALL);
        return 0;
    }

    type = (dctx->md != NULL) ? EVP_MD_type(dctx->md) : NID_sha1;

    ret = ECDSA_sign(type, tbs, tbslen, sig, &sltmp, ec);

    if (ret <= 0)
        return ret;
    *siglen = (size_t)sltmp;
    return 1;
}