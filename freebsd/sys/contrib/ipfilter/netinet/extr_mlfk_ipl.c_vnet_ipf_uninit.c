#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ipf_running; scalar_t__ ipf_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 TYPE_1__ V_ipfmain ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  ipf_destroy_all (TYPE_1__*) ; 
 int /*<<< orphan*/  ipf_event_dereg () ; 
 int /*<<< orphan*/  ipf_pfil_unhook () ; 
 scalar_t__ ipfdetach (TYPE_1__*) ; 

__attribute__((used)) static void
vnet_ipf_uninit(void)
{

	if (V_ipfmain.ipf_refcnt)
		return;

	if (V_ipfmain.ipf_running >= 0) {

		if (ipfdetach(&V_ipfmain) != 0)
			return;

		V_ipfmain.ipf_running = -2;

		ipf_destroy_all(&V_ipfmain);
		if (!IS_DEFAULT_VNET(curvnet)) {
			ipf_event_dereg();
			(void)ipf_pfil_unhook();
		}
	}
}