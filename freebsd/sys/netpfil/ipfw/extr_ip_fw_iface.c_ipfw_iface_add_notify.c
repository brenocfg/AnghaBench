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
struct ipfw_ifc {int /*<<< orphan*/  cbdata; int /*<<< orphan*/  (* cb ) (struct ip_fw_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct ipfw_iface* iface; } ;
struct ipfw_iface {scalar_t__ resolved; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  consumers; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ipfw_ifc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (struct ip_fw_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipfw_iface_add_notify(struct ip_fw_chain *ch, struct ipfw_ifc *ic)
{
	struct ipfw_iface *iif;

	IPFW_UH_WLOCK_ASSERT(ch);
	IPFW_WLOCK_ASSERT(ch);

	iif = ic->iface;
	
	TAILQ_INSERT_TAIL(&iif->consumers, ic, next);
	if (iif->resolved != 0)
		ic->cb(ch, ic->cbdata, iif->ifindex);
}