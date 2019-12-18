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
typedef  int /*<<< orphan*/  ECDSA_SIG ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECDSA_SIG_NEW ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

ECDSA_SIG *ECDSA_SIG_new(void)
{
    ECDSA_SIG *sig = OPENSSL_zalloc(sizeof(*sig));
    if (sig == NULL)
        ECerr(EC_F_ECDSA_SIG_NEW, ERR_R_MALLOC_FAILURE);
    return sig;
}