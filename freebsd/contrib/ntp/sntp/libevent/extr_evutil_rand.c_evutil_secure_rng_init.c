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
 int /*<<< orphan*/  ARC4_LOCK_ () ; 
 int /*<<< orphan*/  ARC4_UNLOCK_ () ; 
 scalar_t__ arc4_seeded_ok ; 
 int /*<<< orphan*/  arc4_stir () ; 

int
evutil_secure_rng_init(void)
{
	int val;

	ARC4_LOCK_();
	if (!arc4_seeded_ok)
		arc4_stir();
	val = arc4_seeded_ok ? 0 : -1;
	ARC4_UNLOCK_();
	return val;
}