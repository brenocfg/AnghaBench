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
 int crypto_onetimeauth_poly1305_verify (unsigned char const*,unsigned char const*,unsigned long long,unsigned char const*) ; 

int
crypto_onetimeauth_verify(const unsigned char *h, const unsigned char *in,
                          unsigned long long inlen, const unsigned char *k)
{
    return crypto_onetimeauth_poly1305_verify(h, in, inlen, k);
}