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
 int crypto_box_BEFORENMBYTES ; 
 scalar_t__ crypto_box_beforenm (unsigned char*,unsigned char const*,unsigned char const*) ; 
 int crypto_box_open_detached_afternm (unsigned char*,unsigned char const*,unsigned char const*,unsigned long long,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_box_open_detached(unsigned char *m, const unsigned char *c,
                         const unsigned char *mac,
                         unsigned long long clen, const unsigned char *n,
                         const unsigned char *pk, const unsigned char *sk)
{
    unsigned char k[crypto_box_BEFORENMBYTES];
    int           ret;

    if (crypto_box_beforenm(k, pk, sk) != 0) {
        return -1;
    }
    ret = crypto_box_open_detached_afternm(m, c, mac, clen, n, k);
    sodium_memzero(k, sizeof k);

    return ret;
}