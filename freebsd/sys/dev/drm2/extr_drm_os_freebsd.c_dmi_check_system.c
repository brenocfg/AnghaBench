#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dmi_system_id {scalar_t__ (* callback ) (struct dmi_system_id const*) ;TYPE_1__* matches; } ;
struct TYPE_2__ {scalar_t__ slot; } ;

/* Variables and functions */
 scalar_t__ dmi_found (struct dmi_system_id const*) ; 
 scalar_t__ stub1 (struct dmi_system_id const*) ; 

bool
dmi_check_system(const struct dmi_system_id *sysid)
{
	const struct dmi_system_id *dsi;
	bool res;

	for (res = false, dsi = sysid; dsi->matches[0].slot != 0 ; dsi++) {
		if (dmi_found(dsi)) {
			res = true;
			if (dsi->callback != NULL && dsi->callback(dsi))
				break;
		}
	}
	return (res);
}