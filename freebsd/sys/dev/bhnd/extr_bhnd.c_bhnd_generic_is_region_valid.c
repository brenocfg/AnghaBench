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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
 scalar_t__ bhnd_get_port_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_get_region_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
bhnd_generic_is_region_valid(device_t dev, device_t child,
    bhnd_port_type type, u_int port, u_int region)
{
	if (port >= bhnd_get_port_count(child, type))
		return (false);

	if (region >= bhnd_get_region_count(child, type, port))
		return (false);

	return (true);
}