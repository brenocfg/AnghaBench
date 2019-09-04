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
typedef  int /*<<< orphan*/  crypto_auth_hmacsha256_state ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_auth_hmacsha256_KEYBYTES ; 
 int /*<<< orphan*/  crypto_auth_hmacsha256_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  crypto_auth_hmacsha256_init (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_auth_hmacsha256_update (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 

int
crypto_auth_hmacsha256(unsigned char *out, const unsigned char *in,
                       unsigned long long inlen, const unsigned char *k)
{
    crypto_auth_hmacsha256_state state;

    crypto_auth_hmacsha256_init(&state, k, crypto_auth_hmacsha256_KEYBYTES);
    crypto_auth_hmacsha256_update(&state, in, inlen);
    crypto_auth_hmacsha256_final(&state, out);

    return 0;
}