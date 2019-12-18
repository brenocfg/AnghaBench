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
typedef  int /*<<< orphan*/  uint16_t ;
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 struct namedobj_instance* CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct named_object* ipfw_objhash_lookup_kidx (struct namedobj_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct named_object *
nat64clat_findbykidx(struct ip_fw_chain *ch, uint16_t idx)
{
	struct namedobj_instance *ni;
	struct named_object *no;

	IPFW_UH_WLOCK_ASSERT(ch);
	ni = CHAIN_TO_SRV(ch);
	no = ipfw_objhash_lookup_kidx(ni, idx);
	KASSERT(no != NULL, ("NAT with index %d not found", idx));

	return (no);
}