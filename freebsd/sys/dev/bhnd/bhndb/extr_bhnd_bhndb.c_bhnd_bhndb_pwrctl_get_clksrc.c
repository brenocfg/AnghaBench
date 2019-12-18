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
typedef  int /*<<< orphan*/  bhnd_clksrc ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PWRCTL_HOSTB_GET_CLKSRC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bhnd_clksrc
bhnd_bhndb_pwrctl_get_clksrc(device_t dev, device_t child,
	bhnd_clock clock)
{
	/* Delegate to parent bridge */
	return (BHND_PWRCTL_HOSTB_GET_CLKSRC(device_get_parent(dev), child,
	    clock));
}