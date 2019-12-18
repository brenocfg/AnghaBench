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
typedef  scalar_t__ uint16_t ;
struct named_object {scalar_t__ kidx; int /*<<< orphan*/  refcnt; } ;
struct ip_fw_chain {int n_rules; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  EACTION_DEBUG (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  IPFW_TLV_EACTION ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  default_eaction_typename ; 
 int /*<<< orphan*/  ipfw_dyn_reset_eaction (struct ip_fw_chain*,scalar_t__,scalar_t__,scalar_t__) ; 
 struct named_object* ipfw_objhash_lookup_name_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_reset_eaction (struct ip_fw_chain*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
reset_eaction_rules(struct ip_fw_chain *ch, uint16_t eaction_id,
    uint16_t instance_id, bool reset_rules)
{
	struct named_object *no;
	int i;

	IPFW_UH_WLOCK_ASSERT(ch);

	no = ipfw_objhash_lookup_name_type(CHAIN_TO_SRV(ch), 0,
	    IPFW_TLV_EACTION, default_eaction_typename);
	if (no == NULL)
		panic("Default external action handler is not found");
	if (eaction_id == no->kidx)
		panic("Wrong eaction_id");

	EACTION_DEBUG("Going to replace id %u with %u", eaction_id, no->kidx);
	IPFW_WLOCK(ch);
	/*
	 * Reset eaction objects only if it is referenced by rules.
	 * But always reset objects for orphaned dynamic states.
	 */
	if (reset_rules) {
		for (i = 0; i < ch->n_rules; i++) {
			/*
			 * Refcount on the original object will be just
			 * ignored on destroy. Refcount on default_eaction
			 * will be decremented on rule deletion, thus we
			 * need to reference default_eaction object.
			 */
			if (ipfw_reset_eaction(ch, ch->map[i], eaction_id,
			    no->kidx, instance_id) != 0)
				no->refcnt++;
		}
	}
	/*
	 * Reset eaction opcodes for orphaned dynamic states.
	 * Since parent rules are already deleted, we don't need to
	 * reference named object of default_eaction.
	 */
	ipfw_dyn_reset_eaction(ch, eaction_id, no->kidx, instance_id);
	IPFW_WUNLOCK(ch);
}