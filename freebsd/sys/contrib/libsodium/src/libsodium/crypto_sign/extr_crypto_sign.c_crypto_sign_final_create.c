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
typedef  int /*<<< orphan*/  crypto_sign_state ;

/* Variables and functions */
 int crypto_sign_ed25519ph_final_create (int /*<<< orphan*/ *,unsigned char*,unsigned long long*,unsigned char const*) ; 

int
crypto_sign_final_create(crypto_sign_state *state, unsigned char *sig,
                         unsigned long long *siglen_p, const unsigned char *sk)
{
    return crypto_sign_ed25519ph_final_create(state, sig, siglen_p, sk);
}