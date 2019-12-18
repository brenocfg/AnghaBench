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
struct TYPE_3__ {int /*<<< orphan*/  ktmp; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ SIPHASH_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
#define  EVP_PKEY_CTRL_DIGESTINIT 131 
#define  EVP_PKEY_CTRL_MD 130 
#define  EVP_PKEY_CTRL_SET_DIGEST_SIZE 129 
#define  EVP_PKEY_CTRL_SET_MAC_KEY 128 
 int /*<<< orphan*/  EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_CTX_get_data (int /*<<< orphan*/ *) ; 
 unsigned char* EVP_PKEY_get0_siphash (int /*<<< orphan*/ ,size_t*) ; 
 size_t SIPHASH_KEY_SIZE ; 
 int SipHash_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SipHash_set_hash_size (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pkey_siphash_ctrl(EVP_PKEY_CTX *ctx, int type, int p1, void *p2)
{
    SIPHASH_PKEY_CTX *pctx = EVP_PKEY_CTX_get_data(ctx);
    const unsigned char *key;
    size_t len;

    switch (type) {

    case EVP_PKEY_CTRL_MD:
        /* ignore */
        break;

    case EVP_PKEY_CTRL_SET_DIGEST_SIZE:
        return SipHash_set_hash_size(&pctx->ctx, p1);

    case EVP_PKEY_CTRL_SET_MAC_KEY:
    case EVP_PKEY_CTRL_DIGESTINIT:
        if (type == EVP_PKEY_CTRL_SET_MAC_KEY) {
            /* user explicitly setting the key */
            key = p2;
            len = p1;
        } else {
            /* user indirectly setting the key via EVP_DigestSignInit */
            key = EVP_PKEY_get0_siphash(EVP_PKEY_CTX_get0_pkey(ctx), &len);
        }
        if (key == NULL || len != SIPHASH_KEY_SIZE ||
            !ASN1_OCTET_STRING_set(&pctx->ktmp, key, len))
            return 0;
        /* use default rounds (2,4) */
        return SipHash_Init(&pctx->ctx, ASN1_STRING_get0_data(&pctx->ktmp),
                            0, 0);

    default:
        return -2;

    }
    return 1;
}