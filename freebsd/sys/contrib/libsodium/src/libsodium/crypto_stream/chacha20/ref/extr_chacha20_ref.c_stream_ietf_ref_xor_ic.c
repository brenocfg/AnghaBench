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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct chacha_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STORE32_LE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chacha20_encrypt_bytes (struct chacha_ctx*,unsigned char const*,unsigned char*,unsigned long long) ; 
 int /*<<< orphan*/  chacha_ietf_ivsetup (struct chacha_ctx*,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chacha_keysetup (struct chacha_ctx*,unsigned char const*) ; 
 int /*<<< orphan*/  sodium_memzero (struct chacha_ctx*,int) ; 

__attribute__((used)) static int
stream_ietf_ref_xor_ic(unsigned char *c, const unsigned char *m,
                       unsigned long long mlen, const unsigned char *n,
                       uint32_t ic, const unsigned char *k)
{
    struct chacha_ctx ctx;
    uint8_t           ic_bytes[4];

    if (!mlen) {
        return 0;
    }
    STORE32_LE(ic_bytes, ic);
    chacha_keysetup(&ctx, k);
    chacha_ietf_ivsetup(&ctx, n, ic_bytes);
    chacha20_encrypt_bytes(&ctx, m, c, mlen);
    sodium_memzero(&ctx, sizeof ctx);

    return 0;
}