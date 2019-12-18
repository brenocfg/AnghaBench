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
struct named_object {int dummy; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  EACTION_DEBUG (char*,int /*<<< orphan*/ ) ; 
 struct named_object* ipfw_objhash_lookup_kidx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct named_object *
eaction_findbykidx(struct ip_fw_chain *ch, uint16_t idx)
{

	EACTION_DEBUG("kidx %u", idx);
	return (ipfw_objhash_lookup_kidx(CHAIN_TO_SRV(ch), idx));
}