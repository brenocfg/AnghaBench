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
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  _crypto_box_seal_nonce (unsigned char*,unsigned char const*,unsigned char const*) ; 
 int crypto_box_NONCEBYTES ; 
 unsigned long long crypto_box_PUBLICKEYBYTES ; 
 unsigned long long crypto_box_SEALBYTES ; 
 int crypto_box_open_easy (unsigned char*,unsigned char const*,unsigned long long,unsigned char*,unsigned char const*,unsigned char const*) ; 

int
crypto_box_seal_open(unsigned char *m, const unsigned char *c,
                     unsigned long long clen,
                     const unsigned char *pk, const unsigned char *sk)
{
    unsigned char nonce[crypto_box_NONCEBYTES];

    if (clen < crypto_box_SEALBYTES) {
        return -1;
    }
    _crypto_box_seal_nonce(nonce, c, pk);

    COMPILER_ASSERT(crypto_box_PUBLICKEYBYTES < crypto_box_SEALBYTES);
    return crypto_box_open_easy(m, c + crypto_box_PUBLICKEYBYTES,
                                clen - crypto_box_PUBLICKEYBYTES,
                                nonce, c, sk);
}