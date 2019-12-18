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
 char* arc4random_urandom_filename ; 

int
evutil_secure_rng_set_urandom_device_file(char *fname)
{
#ifdef TRY_SEED_URANDOM
	ARC4_LOCK_();
	arc4random_urandom_filename = fname;
	ARC4_UNLOCK_();
#endif
	return 0;
}