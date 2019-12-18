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
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  EACTION_DEBUG (char*) ; 
 int /*<<< orphan*/  IPFW_DEL_OBJ_REWRITER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPFW_TLV_EACTION ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  default_eaction_typename ; 
 int /*<<< orphan*/  destroy_eaction_obj (struct ip_fw_chain*,struct named_object*) ; 
 int /*<<< orphan*/  eaction_opcodes ; 
 struct named_object* ipfw_objhash_lookup_name_type (struct namedobj_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipfw_eaction_uninit(struct ip_fw_chain *ch, int last)
{
	struct namedobj_instance *ni;
	struct named_object *no;

	ni = CHAIN_TO_SRV(ch);

	IPFW_UH_WLOCK(ch);
	no = ipfw_objhash_lookup_name_type(ni, 0, IPFW_TLV_EACTION,
	    default_eaction_typename);
	if (no != NULL)
		destroy_eaction_obj(ch, no);
	IPFW_UH_WUNLOCK(ch);
	IPFW_DEL_OBJ_REWRITER(last, eaction_opcodes);
	EACTION_DEBUG("External actions support uninitialized");
}