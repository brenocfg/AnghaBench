#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned char* privkey; unsigned char* pubkey; } ;
struct TYPE_12__ {TYPE_4__* peerkey; TYPE_2__* pkey; } ;
struct TYPE_10__ {TYPE_6__* ecx; } ;
struct TYPE_11__ {TYPE_3__ pkey; } ;
struct TYPE_8__ {TYPE_6__* ecx; } ;
struct TYPE_9__ {TYPE_1__ pkey; } ;
typedef  TYPE_5__ EVP_PKEY_CTX ;
typedef  TYPE_6__ ECX_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_VALIDATE_ECX_DERIVE ; 
 int /*<<< orphan*/  EC_R_INVALID_PEER_KEY ; 
 int /*<<< orphan*/  EC_R_INVALID_PRIVATE_KEY ; 
 int /*<<< orphan*/  EC_R_KEYS_NOT_SET ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_ecx_derive(EVP_PKEY_CTX *ctx, unsigned char *key,
                                          size_t *keylen,
                                          const unsigned char **privkey,
                                          const unsigned char **pubkey)
{
    const ECX_KEY *ecxkey, *peerkey;

    if (ctx->pkey == NULL || ctx->peerkey == NULL) {
        ECerr(EC_F_VALIDATE_ECX_DERIVE, EC_R_KEYS_NOT_SET);
        return 0;
    }
    ecxkey = ctx->pkey->pkey.ecx;
    peerkey = ctx->peerkey->pkey.ecx;
    if (ecxkey == NULL || ecxkey->privkey == NULL) {
        ECerr(EC_F_VALIDATE_ECX_DERIVE, EC_R_INVALID_PRIVATE_KEY);
        return 0;
    }
    if (peerkey == NULL) {
        ECerr(EC_F_VALIDATE_ECX_DERIVE, EC_R_INVALID_PEER_KEY);
        return 0;
    }
    *privkey = ecxkey->privkey;
    *pubkey = peerkey->pubkey;

    return 1;
}