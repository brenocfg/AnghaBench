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
struct tp_entry {int /*<<< orphan*/  status; int /*<<< orphan*/  port_no; } ;
struct ifbareq {int ifba_flags; int /*<<< orphan*/  ifba_ifsname; } ;

/* Variables and functions */
 int IFBAF_STATIC ; 
 int IFBAF_TYPEMASK ; 
 int /*<<< orphan*/  TpFdbStatus_learned ; 
 int /*<<< orphan*/  TpFdbStatus_mgmt ; 
 int /*<<< orphan*/  if_nametoindex (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bridge_addrs_info_ifaddrlist(struct ifbareq *ifba, struct tp_entry *tpe)
{
	tpe->port_no = if_nametoindex(ifba->ifba_ifsname);

	if ((ifba->ifba_flags & IFBAF_TYPEMASK) == IFBAF_STATIC)
		tpe->status = TpFdbStatus_mgmt;
	else
		tpe->status = TpFdbStatus_learned;
}