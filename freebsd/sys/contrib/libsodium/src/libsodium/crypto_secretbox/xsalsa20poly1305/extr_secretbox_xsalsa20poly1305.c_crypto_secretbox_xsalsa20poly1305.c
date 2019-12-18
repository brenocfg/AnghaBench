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
 int /*<<< orphan*/  crypto_onetimeauth_poly1305 (unsigned char*,unsigned char*,unsigned long long,unsigned char*) ; 
 int /*<<< orphan*/  crypto_stream_xsalsa20_xor (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,unsigned char const*) ; 

int
crypto_secretbox_xsalsa20poly1305(unsigned char *c, const unsigned char *m,
                                  unsigned long long mlen,
                                  const unsigned char *n,
                                  const unsigned char *k)
{
    int i;

    if (mlen < 32) {
        return -1;
    }
    crypto_stream_xsalsa20_xor(c, m, mlen, n, k);
    crypto_onetimeauth_poly1305(c + 16, c + 32, mlen - 32, c);
    for (i = 0; i < 16; ++i) {
        c[i] = 0;
    }
    return 0;
}