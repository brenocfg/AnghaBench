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
struct TYPE_2__ {int /*<<< orphan*/  kidx; } ;
struct nat64lsn_cfg {TYPE_1__ no; } ;
struct ip_fw_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_TO_SRV (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  ipfw_objhash_del (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ipfw_objhash_free_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nat64lsn_detach_config(struct ip_fw_chain *ch, struct nat64lsn_cfg *cfg)
{

	IPFW_UH_WLOCK_ASSERT(ch);

	ipfw_objhash_del(CHAIN_TO_SRV(ch), &cfg->no);
	ipfw_objhash_free_idx(CHAIN_TO_SRV(ch), cfg->no.kidx);
}