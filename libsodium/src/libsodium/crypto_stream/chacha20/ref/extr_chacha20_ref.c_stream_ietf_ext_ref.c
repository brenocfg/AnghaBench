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
struct chacha_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  chacha20_encrypt_bytes (struct chacha_ctx*,unsigned char*,unsigned char*,unsigned long long) ; 
 int /*<<< orphan*/  chacha_ietf_ivsetup (struct chacha_ctx*,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chacha_keysetup (struct chacha_ctx*,unsigned char const*) ; 
 int crypto_stream_chacha20_KEYBYTES ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  sodium_memzero (struct chacha_ctx*,int) ; 

__attribute__((used)) static int
stream_ietf_ext_ref(unsigned char *c, unsigned long long clen,
                    const unsigned char *n, const unsigned char *k)
{
    struct chacha_ctx ctx;

    if (!clen) {
        return 0;
    }
    COMPILER_ASSERT(crypto_stream_chacha20_KEYBYTES == 256 / 8);
    chacha_keysetup(&ctx, k);
    chacha_ietf_ivsetup(&ctx, n, NULL);
    memset(c, 0, clen);
    chacha20_encrypt_bytes(&ctx, c, c, clen);
    sodium_memzero(&ctx, sizeof ctx);

    return 0;
}