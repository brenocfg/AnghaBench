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
 int ENXIO ; 
 int /*<<< orphan*/  KEYBOARD_NAME ; 
 scalar_t__ resource_disabled (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kbdmux_probe(int unit, void *arg, int flags)
{
	if (resource_disabled(KEYBOARD_NAME, unit))
		return (ENXIO);

	return (0);
}