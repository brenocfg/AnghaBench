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
struct bhnd_core_match {int dummy; } ;
struct bhnd_core_info {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int BHNDB_GET_HOSTB_CORE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bhnd_core_info*) ; 
 int /*<<< orphan*/ * bhnd_bus_match_child (int /*<<< orphan*/ *,struct bhnd_core_match*) ; 
 struct bhnd_core_match bhnd_core_get_match_desc (struct bhnd_core_info*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
bhnd_bhndb_find_hostb_device(device_t dev)
{
	struct bhnd_core_info	 core;
	struct bhnd_core_match	 md;
	int			 error;

	/* Ask the bridge for the hostb core info */
	if ((error = BHNDB_GET_HOSTB_CORE(device_get_parent(dev), dev, &core)))
		return (NULL);

	/* Find the corresponding bus device */
	md = bhnd_core_get_match_desc(&core);
	return (bhnd_bus_match_child(dev, &md));
}