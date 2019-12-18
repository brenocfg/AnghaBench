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
 int /*<<< orphan*/ * bcops ; 
 int /*<<< orphan*/  indy_sc_enable () ; 
 int /*<<< orphan*/  indy_sc_ops ; 
 scalar_t__ indy_sc_probe () ; 

void indy_sc_init(void)
{
	if (indy_sc_probe()) {
		indy_sc_enable();
		bcops = &indy_sc_ops;
	}
}