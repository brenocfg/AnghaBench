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
 int /*<<< orphan*/  crypto_core_salsa2012 (unsigned char*,unsigned char*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_stream_salsa2012(unsigned char *c, unsigned long long clen,
                        const unsigned char *n, const unsigned char *k)
{
    unsigned char in[16];
    unsigned char block[64];
    unsigned char kcopy[32];
    unsigned int  i;
    unsigned int  u;

    if (!clen) {
        return 0;
    }
    for (i = 0; i < 32; ++i) {
        kcopy[i] = k[i];
    }
    for (i = 0; i < 8; ++i) {
        in[i] = n[i];
    }
    for (i = 8; i < 16; ++i) {
        in[i] = 0;
    }
    while (clen >= 64) {
        crypto_core_salsa2012(c, in, kcopy, NULL);
        u = 1;
        for (i = 8; i < 16; ++i) {
            u += (unsigned int)in[i];
            in[i] = u;
            u >>= 8;
        }
        clen -= 64;
        c += 64;
    }
    if (clen) {
        crypto_core_salsa2012(block, in, kcopy, NULL);
        for (i = 0; i < (unsigned int)clen; ++i) {
            c[i] = block[i];
        }
    }
    sodium_memzero(block, sizeof block);
    sodium_memzero(kcopy, sizeof kcopy);

    return 0;
}