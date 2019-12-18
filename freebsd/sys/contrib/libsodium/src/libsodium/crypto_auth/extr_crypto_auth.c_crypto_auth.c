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
 int crypto_auth_hmacsha512256 (unsigned char*,unsigned char const*,unsigned long long,unsigned char const*) ; 

int
crypto_auth(unsigned char *out, const unsigned char *in,
            unsigned long long inlen, const unsigned char *k)
{
    return crypto_auth_hmacsha512256(out, in, inlen, k);
}