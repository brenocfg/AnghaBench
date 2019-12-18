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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int SIF_INITDOMAIN ; 
 int /*<<< orphan*/  pcifront ; 
 TYPE_1__* xen_start_info ; 
 int /*<<< orphan*/  xenbus_register_frontend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pcifront_init(void *unused)
{
	if ((xen_start_info->flags & SIF_INITDOMAIN))
		return;

	DPRINTF("xenbus registering\n");

	xenbus_register_frontend(&pcifront);
}