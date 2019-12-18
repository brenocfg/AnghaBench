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
struct ipfw_ifc {struct ipfw_iface* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;
struct ipfw_iface {TYPE_1__ no; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 

void
ipfw_iface_unref(struct ip_fw_chain *ch, struct ipfw_ifc *ic)
{
	struct ipfw_iface *iif;

	IPFW_UH_WLOCK_ASSERT(ch);

	iif = ic->iface;
	ic->iface = NULL;

	iif->no.refcnt--;
	/* TODO: check for references & delete */
}