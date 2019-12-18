#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  k; int /*<<< orphan*/  nonce; } ;
typedef  TYPE_1__ crypto_secretstream_xchacha20poly1305_state ;
typedef  unsigned char crypto_onetimeauth_poly1305_state ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_COUNTER (TYPE_1__*) ; 
 int /*<<< orphan*/  STATE_INONCE (TYPE_1__*) ; 
 int /*<<< orphan*/  STORE64_LE (unsigned char*,int) ; 
 int /*<<< orphan*/  XOR_BUF (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* _pad0 ; 
 int crypto_onetimeauth_poly1305_BYTES ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_final (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_init (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_onetimeauth_poly1305_update (unsigned char*,unsigned char const*,int) ; 
 unsigned long long crypto_secretstream_xchacha20poly1305_ABYTES ; 
 int /*<<< orphan*/  crypto_secretstream_xchacha20poly1305_COUNTERBYTES ; 
 int /*<<< orphan*/  crypto_secretstream_xchacha20poly1305_INONCEBYTES ; 
 unsigned long long crypto_secretstream_xchacha20poly1305_MESSAGEBYTES_MAX ; 
 unsigned char crypto_secretstream_xchacha20poly1305_TAG_REKEY ; 
 int /*<<< orphan*/  crypto_secretstream_xchacha20poly1305_rekey (TYPE_1__*) ; 
 int /*<<< orphan*/  crypto_stream_chacha20_ietf (unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_stream_chacha20_ietf_xor_ic (unsigned char*,unsigned char const*,unsigned long long,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sodium_increment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sodium_is_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sodium_memcmp (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 
 int /*<<< orphan*/  sodium_misuse () ; 

int
crypto_secretstream_xchacha20poly1305_pull
   (crypto_secretstream_xchacha20poly1305_state *state,
    unsigned char *m, unsigned long long *mlen_p, unsigned char *tag_p,
    const unsigned char *in, unsigned long long inlen,
    const unsigned char *ad, unsigned long long adlen)
{
    crypto_onetimeauth_poly1305_state poly1305_state;
    unsigned char                     block[64U];
    unsigned char                     slen[8U];
    unsigned char                     mac[crypto_onetimeauth_poly1305_BYTES];
    const unsigned char              *c;
    const unsigned char              *stored_mac;
    unsigned long long                mlen;
    unsigned char                     tag;

    if (mlen_p != NULL) {
        *mlen_p = 0U;
    }
    if (tag_p != NULL) {
        *tag_p = 0xff;
    }
    if (inlen < crypto_secretstream_xchacha20poly1305_ABYTES) {
        return -1;
    }
    mlen = inlen - crypto_secretstream_xchacha20poly1305_ABYTES;
    if (mlen > crypto_secretstream_xchacha20poly1305_MESSAGEBYTES_MAX) {
        sodium_misuse();
    }
    crypto_stream_chacha20_ietf(block, sizeof block, state->nonce, state->k);
    crypto_onetimeauth_poly1305_init(&poly1305_state, block);
    sodium_memzero(block, sizeof block);

    crypto_onetimeauth_poly1305_update(&poly1305_state, ad, adlen);
    crypto_onetimeauth_poly1305_update(&poly1305_state, _pad0,
                                       (0x10 - adlen) & 0xf);

    memset(block, 0, sizeof block);
    block[0] = in[0];
    crypto_stream_chacha20_ietf_xor_ic(block, block, sizeof block,
                                       state->nonce, 1U, state->k);
    tag = block[0];
    block[0] = in[0];
    crypto_onetimeauth_poly1305_update(&poly1305_state, block, sizeof block);

    c = in + (sizeof tag);
    crypto_onetimeauth_poly1305_update(&poly1305_state, c, mlen);
    crypto_onetimeauth_poly1305_update
        (&poly1305_state, _pad0, (0x10 - (sizeof block) + mlen) & 0xf);

    STORE64_LE(slen, (uint64_t) adlen);
    crypto_onetimeauth_poly1305_update(&poly1305_state, slen, sizeof slen);
    STORE64_LE(slen, (sizeof block) + mlen);
    crypto_onetimeauth_poly1305_update(&poly1305_state, slen, sizeof slen);

    crypto_onetimeauth_poly1305_final(&poly1305_state, mac);
    sodium_memzero(&poly1305_state, sizeof poly1305_state);

    stored_mac = c + mlen;
    if (sodium_memcmp(mac, stored_mac, sizeof mac) != 0) {
        sodium_memzero(mac, sizeof mac);
        return -1;
    }

    crypto_stream_chacha20_ietf_xor_ic(m, c, mlen, state->nonce, 2U, state->k);
    XOR_BUF(STATE_INONCE(state), mac,
            crypto_secretstream_xchacha20poly1305_INONCEBYTES);
    sodium_increment(STATE_COUNTER(state),
                     crypto_secretstream_xchacha20poly1305_COUNTERBYTES);
    if ((tag & crypto_secretstream_xchacha20poly1305_TAG_REKEY) != 0 ||
        sodium_is_zero(STATE_COUNTER(state),
                       crypto_secretstream_xchacha20poly1305_COUNTERBYTES)) {
        crypto_secretstream_xchacha20poly1305_rekey(state);
    }
    if (mlen_p != NULL) {
        *mlen_p = mlen;
    }
    if (tag_p != NULL) {
        *tag_p = tag;
    }
    return 0;
}