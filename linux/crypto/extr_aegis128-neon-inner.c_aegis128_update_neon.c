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
typedef  int /*<<< orphan*/  uint8x16_t ;
struct aegis128_state {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 int /*<<< orphan*/  aegis_aes_round (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __attribute__((always_inline))
struct aegis128_state aegis128_update_neon(struct aegis128_state st,
					   uint8x16_t m)
{
	m       ^= aegis_aes_round(st.v[4]);
	st.v[4] ^= aegis_aes_round(st.v[3]);
	st.v[3] ^= aegis_aes_round(st.v[2]);
	st.v[2] ^= aegis_aes_round(st.v[1]);
	st.v[1] ^= aegis_aes_round(st.v[0]);
	st.v[0] ^= m;

	return st;
}