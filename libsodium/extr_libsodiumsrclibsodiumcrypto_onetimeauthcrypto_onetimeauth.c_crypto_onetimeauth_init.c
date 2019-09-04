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
typedef  int /*<<< orphan*/  crypto_onetimeauth_state ;
typedef  int /*<<< orphan*/  crypto_onetimeauth_poly1305_state ;

/* Variables and functions */
 int crypto_onetimeauth_poly1305_init (int /*<<< orphan*/ *,unsigned char const*) ; 

int
crypto_onetimeauth_init(crypto_onetimeauth_state *state,
                        const unsigned char *key)
{
    return crypto_onetimeauth_poly1305_init
        ((crypto_onetimeauth_poly1305_state *) state, key);
}