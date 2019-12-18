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
 int /*<<< orphan*/  COMPILER_ASSERT (int) ; 
 int /*<<< orphan*/  poly1305_init (int /*<<< orphan*/ *,unsigned char const*) ; 

__attribute__((used)) static int
crypto_onetimeauth_poly1305_donna_init(crypto_onetimeauth_poly1305_state *state,
                                       const unsigned char *key)
{
    COMPILER_ASSERT(sizeof(crypto_onetimeauth_poly1305_state) >=
        sizeof(poly1305_state_internal_t));
    poly1305_init((poly1305_state_internal_t *) (void *) state, key);

    return 0;
}