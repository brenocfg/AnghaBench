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
 int /*<<< orphan*/  crypto_core_hchacha20 (unsigned char*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_core_hchacha20_INPUTBYTES ; 
 int crypto_core_hchacha20_OUTPUTBYTES ; 
 int crypto_stream_chacha20 (unsigned char*,unsigned long long,unsigned char const*,unsigned char*) ; 
 int crypto_stream_chacha20_KEYBYTES ; 
 scalar_t__ crypto_stream_chacha20_NONCEBYTES ; 
 scalar_t__ crypto_stream_xchacha20_NONCEBYTES ; 

int
crypto_stream_xchacha20(unsigned char *c, unsigned long long clen,
                        const unsigned char *n, const unsigned char *k)
{
    unsigned char k2[crypto_core_hchacha20_OUTPUTBYTES];

    crypto_core_hchacha20(k2, n, k, NULL);
    COMPILER_ASSERT(crypto_stream_chacha20_KEYBYTES <= sizeof k2);
    COMPILER_ASSERT(crypto_stream_chacha20_NONCEBYTES ==
                    crypto_stream_xchacha20_NONCEBYTES -
                        crypto_core_hchacha20_INPUTBYTES);

    return crypto_stream_chacha20(c, clen, n + crypto_core_hchacha20_INPUTBYTES,
                                  k2);
}