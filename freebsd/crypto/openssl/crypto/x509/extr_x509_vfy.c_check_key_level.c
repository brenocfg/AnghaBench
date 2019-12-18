#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int auth_level; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_security_bits (int /*<<< orphan*/ *) ; 
 int NUM_AUTH_LEVELS ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 
 scalar_t__* minbits_table ; 

__attribute__((used)) static int check_key_level(X509_STORE_CTX *ctx, X509 *cert)
{
    EVP_PKEY *pkey = X509_get0_pubkey(cert);
    int level = ctx->param->auth_level;

    /*
     * At security level zero, return without checking for a supported public
     * key type.  Some engines support key types not understood outside the
     * engine, and we only need to understand the key when enforcing a security
     * floor.
     */
    if (level <= 0)
        return 1;

    /* Unsupported or malformed keys are not secure */
    if (pkey == NULL)
        return 0;

    if (level > NUM_AUTH_LEVELS)
        level = NUM_AUTH_LEVELS;

    return EVP_PKEY_security_bits(pkey) >= minbits_table[level - 1];
}