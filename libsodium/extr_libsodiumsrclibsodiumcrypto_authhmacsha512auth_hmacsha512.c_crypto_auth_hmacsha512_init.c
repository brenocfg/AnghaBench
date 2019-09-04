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
 int /*<<< orphan*/  crypto_hash_sha512_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_hash_sha512_update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  sodium_memzero (void*,int) ; 

int
crypto_auth_hmacsha512_init(crypto_auth_hmacsha512_state *state,
                            const unsigned char *key, size_t keylen)
{
    unsigned char pad[128];
    unsigned char khash[64];
    size_t        i;

    if (keylen > 128) {
        crypto_hash_sha512_init(&state->ictx);
        crypto_hash_sha512_update(&state->ictx, key, keylen);
        crypto_hash_sha512_final(&state->ictx, khash);
        key    = khash;
        keylen = 64;
    }
    crypto_hash_sha512_init(&state->ictx);
    memset(pad, 0x36, 128);
    for (i = 0; i < keylen; i++) {
        pad[i] ^= key[i];
    }
    crypto_hash_sha512_update(&state->ictx, pad, 128);

    crypto_hash_sha512_init(&state->octx);
    memset(pad, 0x5c, 128);
    for (i = 0; i < keylen; i++) {
        pad[i] ^= key[i];
    }
    crypto_hash_sha512_update(&state->octx, pad, 128);

    sodium_memzero((void *) pad, sizeof pad);
    sodium_memzero((void *) khash, sizeof khash);

    return 0;
}