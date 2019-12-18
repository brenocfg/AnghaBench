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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  T ;

/* Variables and functions */
 int /*<<< orphan*/  R0 (int) ; 
 int /*<<< orphan*/  R2 (int) ; 
 scalar_t__ a (int /*<<< orphan*/ ) ; 
 scalar_t__ b (int /*<<< orphan*/ ) ; 
 scalar_t__ c (int /*<<< orphan*/ ) ; 
 scalar_t__ d (int /*<<< orphan*/ ) ; 
 scalar_t__ e (int /*<<< orphan*/ ) ; 
 scalar_t__ f (int /*<<< orphan*/ ) ; 
 scalar_t__ g (int /*<<< orphan*/ ) ; 
 scalar_t__ h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
transform(uint32_t state[8], const uint32_t data[16])
{
	uint32_t W[16];
	uint32_t T[8];

	// Copy state[] to working vars.
	memcpy(T, state, sizeof(T));

	// The first 16 operations unrolled
	R0( 0); R0( 1); R0( 2); R0( 3);
	R0( 4); R0( 5); R0( 6); R0( 7);
	R0( 8); R0( 9); R0(10); R0(11);
	R0(12); R0(13); R0(14); R0(15);

	// The remaining 48 operations partially unrolled
	for (unsigned int j = 16; j < 64; j += 16) {
		R2( 0); R2( 1); R2( 2); R2( 3);
		R2( 4); R2( 5); R2( 6); R2( 7);
		R2( 8); R2( 9); R2(10); R2(11);
		R2(12); R2(13); R2(14); R2(15);
	}

	// Add the working vars back into state[].
	state[0] += a(0);
	state[1] += b(0);
	state[2] += c(0);
	state[3] += d(0);
	state[4] += e(0);
	state[5] += f(0);
	state[6] += g(0);
	state[7] += h(0);
}