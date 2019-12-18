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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  crypto_generichash_blake2b_state ;
typedef  int /*<<< orphan*/  blake2b_state ;

/* Variables and functions */
 int blake2b_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
crypto_generichash_blake2b_update(crypto_generichash_blake2b_state *state,
                                  const unsigned char *in,
                                  unsigned long long inlen)
{
    return blake2b_update((blake2b_state *) (void *) state,
                          (const uint8_t *) in, (uint64_t) inlen);
}