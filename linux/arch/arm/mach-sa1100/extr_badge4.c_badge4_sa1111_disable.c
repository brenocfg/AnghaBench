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
 int /*<<< orphan*/  BADGE4_5V_USB ; 
 unsigned int SA1111_DEVID_USB ; 
 int /*<<< orphan*/  badge4_set_5V (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void badge4_sa1111_disable(void *data, unsigned devid)
{
	if (devid == SA1111_DEVID_USB)
		badge4_set_5V(BADGE4_5V_USB, 0);
}