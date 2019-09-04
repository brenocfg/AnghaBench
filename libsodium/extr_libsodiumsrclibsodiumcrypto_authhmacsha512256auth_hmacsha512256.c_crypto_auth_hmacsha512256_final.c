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
 int /*<<< orphan*/  crypto_auth_hmacsha512_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

int
crypto_auth_hmacsha512256_final(crypto_auth_hmacsha512256_state *state,
                                unsigned char                   *out)
{
    unsigned char out0[64];

    crypto_auth_hmacsha512_final((crypto_auth_hmacsha512_state *) state, out0);
    memcpy(out, out0, 32);

    return 0;
}