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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_SET (int /*<<< orphan*/ ,int) ; 
 int BN_mod_word (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LargeSieve ; 
 int SMALL_MAXIMUM ; 
 int /*<<< orphan*/  debug3 (char*,int) ; 
 int /*<<< orphan*/  largebase ; 
 int largebits ; 
 int /*<<< orphan*/  largetries ; 

__attribute__((used)) static void
sieve_large(u_int32_t s)
{
	u_int32_t r, u;

	debug3("sieve_large %u", s);
	largetries++;
	/* r = largebase mod s */
	r = BN_mod_word(largebase, s);
	if (r == 0)
		u = 0; /* s divides into largebase exactly */
	else
		u = s - r; /* largebase+u is first entry divisible by s */

	if (u < largebits * 2) {
		/*
		 * The sieve omits p's and q's divisible by 2, so ensure that
		 * largebase+u is odd. Then, step through the sieve in
		 * increments of 2*s
		 */
		if (u & 0x1)
			u += s; /* Make largebase+u odd, and u even */

		/* Mark all multiples of 2*s */
		for (u /= 2; u < largebits; u += s)
			BIT_SET(LargeSieve, u);
	}

	/* r = p mod s */
	r = (2 * r + 1) % s;
	if (r == 0)
		u = 0; /* s divides p exactly */
	else
		u = s - r; /* p+u is first entry divisible by s */

	if (u < largebits * 4) {
		/*
		 * The sieve omits p's divisible by 4, so ensure that
		 * largebase+u is not. Then, step through the sieve in
		 * increments of 4*s
		 */
		while (u & 0x3) {
			if (SMALL_MAXIMUM - u < s)
				return;
			u += s;
		}

		/* Mark all multiples of 4*s */
		for (u /= 4; u < largebits; u += s)
			BIT_SET(LargeSieve, u);
	}
}