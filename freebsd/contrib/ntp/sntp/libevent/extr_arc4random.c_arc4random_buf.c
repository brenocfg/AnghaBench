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
 scalar_t__ arc4_count ; 
 unsigned char arc4_getbyte () ; 
 int /*<<< orphan*/  arc4_stir () ; 
 int /*<<< orphan*/  arc4_stir_if_needed () ; 

void
arc4random_buf(void *buf_, size_t n)
{
	unsigned char *buf = buf_;
	ARC4_LOCK_();
	arc4_stir_if_needed();
	while (n--) {
		if (--arc4_count <= 0)
			arc4_stir();
		buf[n] = arc4_getbyte();
	}
	ARC4_UNLOCK_();
}