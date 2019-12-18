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
typedef  int /*<<< orphan*/  poly1305_state_internal_t ;
typedef  int /*<<< orphan*/  crypto_onetimeauth_poly1305_state ;

/* Variables and functions */
 int /*<<< orphan*/  poly1305_update (int /*<<< orphan*/ *,unsigned char const*,unsigned long long) ; 

__attribute__((used)) static int
crypto_onetimeauth_poly1305_donna_update(
    crypto_onetimeauth_poly1305_state *state, const unsigned char *in,
    unsigned long long inlen)
{
    poly1305_update((poly1305_state_internal_t *) (void *) state, in, inlen);

    return 0;
}