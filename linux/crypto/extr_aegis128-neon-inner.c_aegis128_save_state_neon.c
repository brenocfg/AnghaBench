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
struct aegis128_state {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 int /*<<< orphan*/  vst1q_u8 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aegis128_save_state_neon(struct aegis128_state st, void *state)
{
	vst1q_u8(state, st.v[0]);
	vst1q_u8(state + 16, st.v[1]);
	vst1q_u8(state + 32, st.v[2]);
	vst1q_u8(state + 48, st.v[3]);
	vst1q_u8(state + 64, st.v[4]);
}