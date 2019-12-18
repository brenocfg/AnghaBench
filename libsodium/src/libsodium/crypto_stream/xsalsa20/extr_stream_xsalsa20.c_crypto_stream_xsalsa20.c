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
 int /*<<< orphan*/  crypto_core_hsalsa20 (unsigned char*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 
 int crypto_stream_salsa20 (unsigned char*,unsigned long long,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  sodium_memzero (unsigned char*,int) ; 

int
crypto_stream_xsalsa20(unsigned char *c, unsigned long long clen,
                       const unsigned char *n, const unsigned char *k)
{
    unsigned char subkey[32];
    int           ret;

    crypto_core_hsalsa20(subkey, n, k, NULL);
    ret = crypto_stream_salsa20(c, clen, n + 16, subkey);
    sodium_memzero(subkey, sizeof subkey);

    return ret;
}