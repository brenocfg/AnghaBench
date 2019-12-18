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
struct ip_fw {int refcnt; } ;
struct TYPE_2__ {int refcnt; } ;
struct dyn_state_obj {TYPE_1__ no; } ;
struct dyn_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct dyn_state_obj* SRV_OBJECT (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_destroy (struct ip_fw_chain*,TYPE_1__*) ; 
 int /*<<< orphan*/  ipfw_free_rule (struct ip_fw*) ; 

__attribute__((used)) static void
dyn_release_rule(struct ip_fw_chain *ch, struct dyn_data *data,
    struct ip_fw *rule, uint16_t kidx)
{
	struct dyn_state_obj *obj;

	IPFW_UH_WLOCK_ASSERT(ch);
	MPASS(kidx != 0);

	obj = SRV_OBJECT(ch, kidx);
	if (obj->no.refcnt == 1)
		dyn_destroy(ch, &obj->no);
	else
		obj->no.refcnt--;

	if (--rule->refcnt == 1)
		ipfw_free_rule(rule);
}