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
struct TYPE_2__ {int /*<<< orphan*/  (* flush_ipi ) () ;} ;

/* Variables and functions */
 TYPE_1__* icp_ops ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  xics_default_distrib_server ; 
 int /*<<< orphan*/  xics_set_cpu_giq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xics_teardown_cpu () ; 

void xics_kexec_teardown_cpu(int secondary)
{
	xics_teardown_cpu();

	icp_ops->flush_ipi();

	/*
	 * Some machines need to have at least one cpu in the GIQ,
	 * so leave the master cpu in the group.
	 */
	if (secondary)
		xics_set_cpu_giq(xics_default_distrib_server, 0);
}