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
struct TYPE_3__ {int /*<<< orphan*/  hs; } ;
typedef  TYPE_1__ crypto_sign_ed25519ph_state ;

/* Variables and functions */
 int _crypto_sign_ed25519_detached (unsigned char*,unsigned long long*,unsigned char*,int,unsigned char const*,int) ; 
 int crypto_hash_sha512_BYTES ; 
 int /*<<< orphan*/  crypto_hash_sha512_final (int /*<<< orphan*/ *,unsigned char*) ; 

int
crypto_sign_ed25519ph_final_create(crypto_sign_ed25519ph_state *state,
                                   unsigned char               *sig,
                                   unsigned long long          *siglen_p,
                                   const unsigned char         *sk)
{
    unsigned char ph[crypto_hash_sha512_BYTES];

    crypto_hash_sha512_final(&state->hs, ph);

    return _crypto_sign_ed25519_detached(sig, siglen_p, ph, sizeof ph, sk, 1);
}