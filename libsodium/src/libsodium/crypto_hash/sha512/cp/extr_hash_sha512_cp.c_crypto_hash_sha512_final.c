#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ crypto_hash_sha512_state ;

/* Variables and functions */
 int /*<<< orphan*/  SHA512_Pad (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64enc_vect (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sodium_memzero (void*,int) ; 

int
crypto_hash_sha512_final(crypto_hash_sha512_state *state, unsigned char *out)
{
    uint64_t tmp64[80 + 8];

    SHA512_Pad(state, tmp64);
    be64enc_vect(out, state->state, 64);
    sodium_memzero((void *) tmp64, sizeof tmp64);
    sodium_memzero((void *) state, sizeof *state);

    return 0;
}