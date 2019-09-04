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
typedef  int /*<<< orphan*/  crypto_auth_hmacsha512_state ;
typedef  int /*<<< orphan*/  crypto_auth_hmacsha512256_state ;

/* Variables and functions */
 int crypto_auth_hmacsha512_init (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int
crypto_auth_hmacsha512256_init(crypto_auth_hmacsha512256_state *state,
                               const unsigned char *key, size_t keylen)
{
    return crypto_auth_hmacsha512_init((crypto_auth_hmacsha512_state *) state,
                                       key, keylen);
}