#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* pkey; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_6__ {TYPE_1__ pkey; } ;
typedef  TYPE_3__ EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int sm2_verify (unsigned char const*,size_t,unsigned char const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkey_sm2_verify(EVP_PKEY_CTX *ctx,
                           const unsigned char *sig, size_t siglen,
                           const unsigned char *tbs, size_t tbslen)
{
    EC_KEY *ec = ctx->pkey->pkey.ec;

    return sm2_verify(tbs, tbslen, sig, siglen, ec);
}