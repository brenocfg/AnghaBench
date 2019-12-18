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
struct bhnd_core_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHNDB_IS_CORE_DISABLED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bhnd_core_info*) ; 
 struct bhnd_core_info bhnd_get_core_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bhnd_bhndb_is_hw_disabled(device_t dev, device_t child)
{
	struct bhnd_core_info core = bhnd_get_core_info(child);

	/* Delegate to parent bridge */
	return (BHNDB_IS_CORE_DISABLED(device_get_parent(dev), dev, &core));
}