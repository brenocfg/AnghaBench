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
typedef  int /*<<< orphan*/  crypto_generichash_state ;
typedef  int /*<<< orphan*/  crypto_generichash_blake2b_state ;

/* Variables and functions */
 int crypto_generichash_blake2b_final (int /*<<< orphan*/ *,unsigned char*,size_t const) ; 

int
crypto_generichash_final(crypto_generichash_state *state,
                         unsigned char *out, const size_t outlen)
{
    return crypto_generichash_blake2b_final
        ((crypto_generichash_blake2b_state *) state, out, outlen);
}