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

/* Variables and functions */
 int /*<<< orphan*/  ptls_minicrypto_secp256r1 ; 
 int /*<<< orphan*/  test_key_exchange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_secp256r1_key_exchange(void)
{
    test_key_exchange(&ptls_minicrypto_secp256r1, &ptls_minicrypto_secp256r1);
}