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
 int crypto_secretbox_MACBYTES ; 
 unsigned long long crypto_secretbox_MESSAGEBYTES_MAX ; 
 int crypto_secretbox_detached (unsigned char*,unsigned char*,unsigned char const*,unsigned long long,unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  sodium_misuse () ; 

int
crypto_secretbox_easy(unsigned char *c, const unsigned char *m,
                      unsigned long long mlen, const unsigned char *n,
                      const unsigned char *k)
{
    if (mlen > crypto_secretbox_MESSAGEBYTES_MAX) {
        sodium_misuse();
    }
    return crypto_secretbox_detached(c + crypto_secretbox_MACBYTES,
                                     c, m, mlen, n, k);
}