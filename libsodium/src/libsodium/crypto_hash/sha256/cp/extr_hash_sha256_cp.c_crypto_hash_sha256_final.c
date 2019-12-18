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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ crypto_hash_sha256_state ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256_Pad (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32enc_vect (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sodium_memzero (void*,int) ; 

int
crypto_hash_sha256_final(crypto_hash_sha256_state *state, unsigned char *out)
{
    uint32_t tmp32[64 + 8];

    SHA256_Pad(state, tmp32);
    be32enc_vect(out, state->state, 32);
    sodium_memzero((void *) tmp32, sizeof tmp32);
    sodium_memzero((void *) state, sizeof *state);

    return 0;
}