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
typedef  unsigned char crypto_onetimeauth_poly1305_state ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  crypto_core_hsalsa20 (unsigned char*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 
 unsigned int crypto_onetimeauth_poly1305_KEYBYTES ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_final (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_init (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_update (unsigned char*,unsigned char*,unsigned long long) ; 
 unsigned int crypto_secretbox_ZEROBYTES ; 
 int crypto_stream_salsa20_KEYBYTES ; 
 int /*<<< orphan*/  crypto_stream_salsa20_xor (unsigned char*,unsigned char*,unsigned long long,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_stream_salsa20_xor_ic (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,unsigned long long) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_secretbox_detached(unsigned char *c, unsigned char *mac,
                          const unsigned char *m,
                          unsigned long long mlen, const unsigned char *n,
                          const unsigned char *k)
{
    crypto_onetimeauth_poly1305_state state;
    unsigned char                     block0[64U];
    unsigned char                     subkey[crypto_stream_salsa20_KEYBYTES];
    unsigned long long                i;
    unsigned long long                mlen0;

    crypto_core_hsalsa20(subkey, n, k, NULL);

    if (((uintptr_t) c > (uintptr_t) m &&
         (uintptr_t) c - (uintptr_t) m < mlen) ||
        ((uintptr_t) m > (uintptr_t) c &&
         (uintptr_t) m - (uintptr_t) c < mlen)) { /* LCOV_EXCL_LINE */
        memmove(c, m, mlen);
        m = c;
    }
    memset(block0, 0U, crypto_secretbox_ZEROBYTES);
    COMPILER_ASSERT(64U >= crypto_secretbox_ZEROBYTES);
    mlen0 = mlen;
    if (mlen0 > 64U - crypto_secretbox_ZEROBYTES) {
        mlen0 = 64U - crypto_secretbox_ZEROBYTES;
    }
    for (i = 0U; i < mlen0; i++) {
        block0[i + crypto_secretbox_ZEROBYTES] = m[i];
    }
    crypto_stream_salsa20_xor(block0, block0,
                              mlen0 + crypto_secretbox_ZEROBYTES,
                              n + 16, subkey);
    COMPILER_ASSERT(crypto_secretbox_ZEROBYTES >=
                    crypto_onetimeauth_poly1305_KEYBYTES);
    crypto_onetimeauth_poly1305_init(&state, block0);

    for (i = 0U; i < mlen0; i++) {
        c[i] = block0[crypto_secretbox_ZEROBYTES + i];
    }
    sodium_memzero(block0, sizeof block0);
    if (mlen > mlen0) {
        crypto_stream_salsa20_xor_ic(c + mlen0, m + mlen0, mlen - mlen0,
                                     n + 16, 1U, subkey);
    }
    sodium_memzero(subkey, sizeof subkey);

    crypto_onetimeauth_poly1305_update(&state, c, mlen);
    crypto_onetimeauth_poly1305_final(&state, mac);
    sodium_memzero(&state, sizeof state);

    return 0;
}