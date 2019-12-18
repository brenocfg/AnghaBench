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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_clock ;

/* Variables and functions */
 int BHND_PWRCTL_HOSTB_GATE_CLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_bhndb_pwrctl_gate_clock(device_t dev, device_t child,
	bhnd_clock clock)
{
	/* Delegate to parent bridge */
	return (BHND_PWRCTL_HOSTB_GATE_CLOCK(device_get_parent(dev), child,
	    clock));
}