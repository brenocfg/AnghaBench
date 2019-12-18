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
struct zyd_rf {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
zyd_al2210_switch_radio(struct zyd_rf *rf, int on)
{
	/* vendor driver does nothing for this RF chip */

	return (0);
}