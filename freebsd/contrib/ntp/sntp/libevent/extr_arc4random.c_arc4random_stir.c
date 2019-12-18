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
 int arc4_stir () ; 

int
arc4random_stir(void)
{
	int val;
	ARC4_LOCK_();
	val = arc4_stir();
	ARC4_UNLOCK_();
	return val;
}