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
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ bhnd_core_matches (struct bhnd_core_info*,struct bhnd_core_match const*) ; 
 struct bhnd_core_info bhnd_get_core_info (int /*<<< orphan*/ *) ; 
 int device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

device_t
bhnd_bus_match_child(device_t bus, const struct bhnd_core_match *desc)
{
	device_t	*devlistp;
	device_t	 match;
	int		 devcnt;
	int		 error;

	error = device_get_children(bus, &devlistp, &devcnt);
	if (error != 0)
		return (NULL);

	match = NULL;
	for (int i = 0; i < devcnt; i++) {
		struct bhnd_core_info ci = bhnd_get_core_info(devlistp[i]);

		if (bhnd_core_matches(&ci, desc)) {
			match = devlistp[i];
			goto done;
		}
	}

done:
	free(devlistp, M_TEMP);
	return match;
}