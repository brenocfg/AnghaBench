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

/* Variables and functions */
 scalar_t__ CRYPTO_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  x25519_scalar_mult (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int X25519(uint8_t out_shared_key[32], const uint8_t private_key[32],
           const uint8_t peer_public_value[32])
{
    static const uint8_t kZeros[32] = {0};
    x25519_scalar_mult(out_shared_key, private_key, peer_public_value);
    /* The all-zero output results when the input is a point of small order. */
    return CRYPTO_memcmp(kZeros, out_shared_key, 32) != 0;
}