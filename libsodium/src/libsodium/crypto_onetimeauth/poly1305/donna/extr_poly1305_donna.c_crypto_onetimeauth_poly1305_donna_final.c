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
 int /*<<< orphan*/  poly1305_finish (int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int
crypto_onetimeauth_poly1305_donna_final(
    crypto_onetimeauth_poly1305_state *state, unsigned char *out)
{
    poly1305_finish((poly1305_state_internal_t *) (void *) state, out);

    return 0;
}