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
 int /*<<< orphan*/  BYTES_BEFORE_RESEED ; 
 int /*<<< orphan*/  arc4_count ; 
 int /*<<< orphan*/  arc4_getbyte () ; 
 int /*<<< orphan*/  arc4_init () ; 
 scalar_t__ arc4_seed () ; 
 int rs_initialized ; 

__attribute__((used)) static int
arc4_stir(void)
{
	int     i;

	if (!rs_initialized) {
		arc4_init();
		rs_initialized = 1;
	}

	if (0 != arc4_seed())
		return -1;

	/*
	 * Discard early keystream, as per recommendations in
	 * "Weaknesses in the Key Scheduling Algorithm of RC4" by
	 * Scott Fluhrer, Itsik Mantin, and Adi Shamir.
	 * http://www.wisdom.weizmann.ac.il/~itsik/RC4/Papers/Rc4_ksa.ps
	 *
	 * Ilya Mironov's "(Not So) Random Shuffles of RC4" suggests that
	 * we drop at least 2*256 bytes, with 12*256 as a conservative
	 * value.
	 *
	 * RFC4345 says to drop 6*256.
	 *
	 * At least some versions of this code drop 4*256, in a mistaken
	 * belief that "words" in the Fluhrer/Mantin/Shamir paper refers
	 * to processor words.
	 *
	 * We add another sect to the cargo cult, and choose 12*256.
	 */
	for (i = 0; i < 12*256; i++)
		(void)arc4_getbyte();

	arc4_count = BYTES_BEFORE_RESEED;

	return 0;
}