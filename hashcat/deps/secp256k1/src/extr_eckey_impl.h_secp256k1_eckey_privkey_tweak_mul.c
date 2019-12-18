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
typedef  int /*<<< orphan*/  secp256k1_scalar ;

/* Variables and functions */
 scalar_t__ secp256k1_scalar_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  secp256k1_scalar_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int secp256k1_eckey_privkey_tweak_mul(secp256k1_scalar *key, const secp256k1_scalar *tweak) {
    if (secp256k1_scalar_is_zero(tweak)) {
        return 0;
    }

    secp256k1_scalar_mul(key, key, tweak);
    return 1;
}