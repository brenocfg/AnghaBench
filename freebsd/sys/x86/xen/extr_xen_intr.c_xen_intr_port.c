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
typedef  int /*<<< orphan*/  xen_intr_handle_t ;
struct xenisrc {int /*<<< orphan*/  xi_port; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;

/* Variables and functions */
 struct xenisrc* xen_intr_isrc (int /*<<< orphan*/ ) ; 

evtchn_port_t
xen_intr_port(xen_intr_handle_t handle)
{
	struct xenisrc *isrc;

	isrc = xen_intr_isrc(handle);
	if (isrc == NULL)
		return (0);
	
	return (isrc->xi_port);
}