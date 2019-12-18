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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  _ARC4_LOCK () ; 
 int /*<<< orphan*/  _ARC4_UNLOCK () ; 
 scalar_t__ arc4_count ; 
 int /*<<< orphan*/  arc4_getbyte () ; 
 int /*<<< orphan*/  arc4_stir () ; 
 int /*<<< orphan*/  arc4_stir_if_needed () ; 

__attribute__((used)) static void
arc4random_buf(void *_buf, size_t n)
{
	u_char *buf = (u_char *)_buf;
	_ARC4_LOCK();
	arc4_stir_if_needed();
	while (n--) {
		if (--arc4_count <= 0)
			arc4_stir();
		buf[n] = arc4_getbyte();
	}
	_ARC4_UNLOCK();
}