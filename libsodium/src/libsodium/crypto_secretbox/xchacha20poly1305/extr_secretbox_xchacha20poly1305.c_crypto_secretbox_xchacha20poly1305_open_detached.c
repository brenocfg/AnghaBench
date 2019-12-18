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

/* Variables and functions */
 int /*<<< orphan*/  crypto_core_hchacha20 (unsigned char*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_onetimeauth_poly1305_verify (unsigned char const*,unsigned char const*,unsigned long long,unsigned char*) ; 
 unsigned int crypto_secretbox_xchacha20poly1305_ZEROBYTES ; 
 int /*<<< orphan*/  crypto_stream_chacha20 (unsigned char*,int,unsigned char const*,unsigned char*) ; 
 int crypto_stream_chacha20_KEYBYTES ; 
 int /*<<< orphan*/  crypto_stream_chacha20_xor (unsigned char*,unsigned char*,unsigned int,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_stream_chacha20_xor_ic (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char const*,unsigned long long) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_secretbox_xchacha20poly1305_open_detached(unsigned char *m,
                                                 const unsigned char *c,
                                                 const unsigned char *mac,
                                                 unsigned long long clen,
                                                 const unsigned char *n,
                                                 const unsigned char *k)
{
    unsigned char      block0[64U];
    unsigned char      subkey[crypto_stream_chacha20_KEYBYTES];
    unsigned long long i;
    unsigned long long mlen0;

    crypto_core_hchacha20(subkey, n, k, NULL);
    crypto_stream_chacha20(block0, crypto_stream_chacha20_KEYBYTES,
                           n + 16, subkey);
    if (crypto_onetimeauth_poly1305_verify(mac, c, clen, block0) != 0) {
        sodium_memzero(subkey, sizeof subkey);
        return -1;
    }
    if (m == NULL) {
        return 0;
    }
    if (((uintptr_t) c >= (uintptr_t) m &&
         (uintptr_t) c - (uintptr_t) m < clen) ||
        ((uintptr_t) m >= (uintptr_t) c &&
         (uintptr_t) m - (uintptr_t) c < clen)) { /* LCOV_EXCL_LINE */
        memmove(m, c, clen);
        c = m;
    }
    mlen0 = clen;
    if (mlen0 > 64U - crypto_secretbox_xchacha20poly1305_ZEROBYTES) {
        mlen0 = 64U - crypto_secretbox_xchacha20poly1305_ZEROBYTES;
    }
    for (i = 0U; i < mlen0; i++) {
        block0[crypto_secretbox_xchacha20poly1305_ZEROBYTES + i] = c[i];
    }
    crypto_stream_chacha20_xor(block0, block0,
                              crypto_secretbox_xchacha20poly1305_ZEROBYTES + mlen0,
                              n + 16, subkey);
    for (i = 0U; i < mlen0; i++) {
        m[i] = block0[i + crypto_secretbox_xchacha20poly1305_ZEROBYTES];
    }
    if (clen > mlen0) {
        crypto_stream_chacha20_xor_ic(m + mlen0, c + mlen0, clen - mlen0,
                                      n + 16, 1U, subkey);
    }
    sodium_memzero(subkey, sizeof subkey);

    return 0;
}