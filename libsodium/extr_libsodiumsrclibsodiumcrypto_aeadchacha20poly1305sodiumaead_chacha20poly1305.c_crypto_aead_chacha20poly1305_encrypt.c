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
 unsigned long long crypto_aead_chacha20poly1305_ABYTES ; 
 unsigned long long crypto_aead_chacha20poly1305_MESSAGEBYTES_MAX ; 
 int crypto_aead_chacha20poly1305_encrypt_detached (unsigned char*,unsigned char*,int /*<<< orphan*/ *,unsigned char const*,unsigned long long,unsigned char const*,unsigned long long,unsigned char const*,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  sodium_misuse () ; 

int
crypto_aead_chacha20poly1305_encrypt(unsigned char *c,
                                     unsigned long long *clen_p,
                                     const unsigned char *m,
                                     unsigned long long mlen,
                                     const unsigned char *ad,
                                     unsigned long long adlen,
                                     const unsigned char *nsec,
                                     const unsigned char *npub,
                                     const unsigned char *k)
{
    unsigned long long clen = 0ULL;
    int                ret;

    if (mlen > crypto_aead_chacha20poly1305_MESSAGEBYTES_MAX) {
        sodium_misuse();
    }
    ret = crypto_aead_chacha20poly1305_encrypt_detached(c,
                                                        c + mlen, NULL,
                                                        m, mlen,
                                                        ad, adlen,
                                                        nsec, npub, k);
    if (clen_p != NULL) {
        if (ret == 0) {
            clen = mlen + crypto_aead_chacha20poly1305_ABYTES;
        }
        *clen_p = clen;
    }
    return ret;
}