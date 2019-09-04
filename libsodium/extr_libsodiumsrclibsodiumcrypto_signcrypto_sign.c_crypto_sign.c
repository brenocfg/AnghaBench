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

/* Variables and functions */
 int crypto_sign_ed25519 (unsigned char*,unsigned long long*,unsigned char const*,unsigned long long,unsigned char const*) ; 

int
crypto_sign(unsigned char *sm, unsigned long long *smlen_p,
            const unsigned char *m, unsigned long long mlen,
            const unsigned char *sk)
{
    return crypto_sign_ed25519(sm, smlen_p, m, mlen, sk);
}