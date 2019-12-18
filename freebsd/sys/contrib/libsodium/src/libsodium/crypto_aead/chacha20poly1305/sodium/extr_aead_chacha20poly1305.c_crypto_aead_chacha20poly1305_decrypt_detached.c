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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  unsigned char crypto_onetimeauth_poly1305_state ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  STORE64_LE (unsigned char*,int /*<<< orphan*/ ) ; 
 int crypto_aead_chacha20poly1305_ABYTES ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_final (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_init (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_update (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  crypto_stream_chacha20 (unsigned char*,int,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  crypto_stream_chacha20_xor_ic (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,unsigned int,unsigned char const*) ; 
 int crypto_verify_16 (unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_aead_chacha20poly1305_decrypt_detached(unsigned char *m,
                                              unsigned char *nsec,
                                              const unsigned char *c,
                                              unsigned long long clen,
                                              const unsigned char *mac,
                                              const unsigned char *ad,
                                              unsigned long long adlen,
                                              const unsigned char *npub,
                                              const unsigned char *k)
{
    crypto_onetimeauth_poly1305_state state;
    unsigned char                     block0[64U];
    unsigned char                     slen[8U];
    unsigned char                     computed_mac[crypto_aead_chacha20poly1305_ABYTES];
    unsigned long long                mlen;
    int                               ret;

    (void) nsec;
    crypto_stream_chacha20(block0, sizeof block0, npub, k);
    crypto_onetimeauth_poly1305_init(&state, block0);
    sodium_memzero(block0, sizeof block0);

    crypto_onetimeauth_poly1305_update(&state, ad, adlen);
    STORE64_LE(slen, (uint64_t) adlen);
    crypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    mlen = clen;
    crypto_onetimeauth_poly1305_update(&state, c, mlen);
    STORE64_LE(slen, (uint64_t) mlen);
    crypto_onetimeauth_poly1305_update(&state, slen, sizeof slen);

    crypto_onetimeauth_poly1305_final(&state, computed_mac);
    sodium_memzero(&state, sizeof state);

    COMPILER_ASSERT(sizeof computed_mac == 16U);
    ret = crypto_verify_16(computed_mac, mac);
    sodium_memzero(computed_mac, sizeof computed_mac);
    if (m == NULL) {
        return ret;
    }
    if (ret != 0) {
        memset(m, 0, mlen);
        return -1;
    }
    crypto_stream_chacha20_xor_ic(m, c, mlen, npub, 1U, k);

    return 0;
}