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
struct ipfw_ifc {struct ipfw_iface* iface; } ;
struct ipfw_iface {int /*<<< orphan*/  consumers; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ipfw_ifc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

void
ipfw_iface_del_notify(struct ip_fw_chain *ch, struct ipfw_ifc *ic)
{
	struct ipfw_iface *iif;

	IPFW_UH_WLOCK_ASSERT(ch);

	iif = ic->iface;
	TAILQ_REMOVE(&iif->consumers, ic, next);
}