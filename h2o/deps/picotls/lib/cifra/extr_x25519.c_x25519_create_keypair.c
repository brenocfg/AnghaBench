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
 int /*<<< orphan*/  X25519_KEY_SIZE ; 
 int /*<<< orphan*/  cf_curve25519_mul_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_minicrypto_random_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void x25519_create_keypair(uint8_t *priv, uint8_t *pub)
{
    ptls_minicrypto_random_bytes(priv, X25519_KEY_SIZE);
    cf_curve25519_mul_base(pub, priv);
}