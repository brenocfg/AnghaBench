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
 int /*<<< orphan*/  arc4lock ; 
 scalar_t__ arc4lockinit ; 
 int /*<<< orphan*/  lock_quick_destroy (int /*<<< orphan*/ *) ; 

void _ARC4_LOCK_DESTROY(void)
{
	if(arc4lockinit) {
		arc4lockinit = 0;
		lock_quick_destroy(&arc4lock);
	}
}