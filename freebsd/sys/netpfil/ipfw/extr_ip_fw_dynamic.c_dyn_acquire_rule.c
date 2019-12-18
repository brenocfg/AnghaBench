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
typedef  int /*<<< orphan*/  uint16_t ;
struct ip_fw_chain {int dummy; } ;
struct ip_fw {int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {scalar_t__ etlv; int /*<<< orphan*/  refcnt; } ;
struct dyn_state_obj {TYPE_1__ no; } ;
struct dyn_data {int flags; } ;

/* Variables and functions */
 int DYN_REFERENCED ; 
 scalar_t__ IPFW_TLV_STATE_NAME ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct dyn_state_obj* SRV_OBJECT (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dyn_acquire_rule(struct ip_fw_chain *ch, struct dyn_data *data,
    struct ip_fw *rule, uint16_t kidx)
{
	struct dyn_state_obj *obj;

	/*
	 * Do not acquire reference twice.
	 * This can happen when rule deletion executed for
	 * the same range, but different ruleset id.
	 */
	if (data->flags & DYN_REFERENCED)
		return;

	IPFW_UH_WLOCK_ASSERT(ch);
	MPASS(kidx != 0);

	data->flags |= DYN_REFERENCED;
	/* Reference the named object */
	obj = SRV_OBJECT(ch, kidx);
	obj->no.refcnt++;
	MPASS(obj->no.etlv == IPFW_TLV_STATE_NAME);

	/* Reference the parent rule */
	rule->refcnt++;
}