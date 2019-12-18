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
typedef  union aegis_block {int dummy; } aegis_block ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_aegis128_update_neon (union aegis_block*,void const*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 

void crypto_aegis128_update_simd(union aegis_block *state, const void *msg)
{
	kernel_neon_begin();
	crypto_aegis128_update_neon(state, msg);
	kernel_neon_end();
}