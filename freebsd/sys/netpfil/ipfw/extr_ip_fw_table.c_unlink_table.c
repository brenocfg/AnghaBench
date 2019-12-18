#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct table_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kidx; } ;
struct table_config {int /*<<< orphan*/  astate; TYPE_1__* ta; scalar_t__ linked; TYPE_2__ no; } ;
struct namedobj_instance {int dummy; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* change_ti ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_NI (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 struct table_info* KIDX_TO_TI (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipfw_objhash_del (struct namedobj_instance*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (struct table_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unlink_table(struct ip_fw_chain *ch, struct table_config *tc)
{
	struct namedobj_instance *ni;
	struct table_info *ti;
	uint16_t kidx;

	IPFW_UH_WLOCK_ASSERT(ch);
	IPFW_WLOCK_ASSERT(ch);

	ni = CHAIN_TO_NI(ch);
	kidx = tc->no.kidx;

	/* Clear state. @ti copy is already saved inside @tc */
	ipfw_objhash_del(ni, &tc->no);
	ti = KIDX_TO_TI(ch, kidx);
	memset(ti, 0, sizeof(struct table_info));
	tc->linked = 0;
	tc->ta->refcnt--;

	/* Notify algo on real @ti address */
	if (tc->ta->change_ti != NULL)
		tc->ta->change_ti(tc->astate, NULL);
}