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
struct aegis128_state {int dummy; } ;

/* Variables and functions */
 struct aegis128_state aegis128_load_state_neon (void*) ; 
 int /*<<< orphan*/  aegis128_save_state_neon (struct aegis128_state,void*) ; 
 struct aegis128_state aegis128_update_neon (struct aegis128_state,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preload_sbox () ; 
 int /*<<< orphan*/  vld1q_u8 (void const*) ; 

void crypto_aegis128_update_neon(void *state, const void *msg)
{
	struct aegis128_state st = aegis128_load_state_neon(state);

	preload_sbox();

	st = aegis128_update_neon(st, vld1q_u8(msg));

	aegis128_save_state_neon(st, state);
}