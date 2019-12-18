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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int grh_present; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  ib_gid; } ;
struct ib_user_mad {TYPE_1__ addr; } ;
struct ib_mad_addr {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; scalar_t__ flow_label; int /*<<< orphan*/  ib_gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 

int umad_set_grh(void *umad, void *mad_addr)
{
	struct ib_user_mad *mad = umad;
	struct ib_mad_addr *addr = mad_addr;

	if (mad_addr) {
		mad->addr.grh_present = 1;
		mad->addr.ib_gid = addr->ib_gid;
		/* The definition for umad_set_grh requires that the input be
		 * in host order */
		mad->addr.flow_label = htobe32((uint32_t)addr->flow_label);
		mad->addr.hop_limit = addr->hop_limit;
		mad->addr.traffic_class = addr->traffic_class;
	} else
		mad->addr.grh_present = 0;
	return 0;
}