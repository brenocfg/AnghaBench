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
struct TYPE_3__ {int /*<<< orphan*/  octx; int /*<<< orphan*/  ictx; } ;
typedef  TYPE_1__ crypto_auth_hmacsha512_state ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_hash_sha512_update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  sodium_memzero (void*,int) ; 

int
crypto_auth_hmacsha512_final(crypto_auth_hmacsha512_state *state,
                             unsigned char                *out)
{
    unsigned char ihash[64];

    crypto_hash_sha512_final(&state->ictx, ihash);
    crypto_hash_sha512_update(&state->octx, ihash, 64);
    crypto_hash_sha512_final(&state->octx, out);

    sodium_memzero((void *) ihash, sizeof ihash);

    return 0;
}