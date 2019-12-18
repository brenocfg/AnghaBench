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
struct evutil_weakrand_state {int seed; } ;
typedef  int /*<<< orphan*/  ev_int32_t ;

/* Variables and functions */

ev_int32_t
evutil_weakrand_(struct evutil_weakrand_state *state)
{
	/* This RNG implementation is a linear congruential generator, with
	 * modulus 2^31, multiplier 1103515245, and addend 12345.  It's also
	 * used by OpenBSD, and by Glibc's TYPE_0 RNG.
	 *
	 * The linear congruential generator is not an industrial-strength
	 * RNG!  It's fast, but it can have higher-order patterns.  Notably,
	 * the low bits tend to have periodicity.
	 */
	state->seed = ((state->seed) * 1103515245 + 12345) & 0x7fffffff;
	return (ev_int32_t)(state->seed);
}