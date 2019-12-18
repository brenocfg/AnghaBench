#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  set; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  clat_plen; int /*<<< orphan*/  clat_prefix; int /*<<< orphan*/  plat_plen; int /*<<< orphan*/  plat_prefix; } ;
struct nat64clat_cfg {TYPE_1__ no; TYPE_2__ base; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  set; int /*<<< orphan*/  clat_plen; int /*<<< orphan*/  clat_prefix; int /*<<< orphan*/  plat_plen; int /*<<< orphan*/  plat_prefix; } ;
typedef  TYPE_3__ ipfw_nat64clat_cfg ;

/* Variables and functions */
 int NAT64CLAT_FLAGSMASK ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nat64clat_export_config(struct ip_fw_chain *ch, struct nat64clat_cfg *cfg,
    ipfw_nat64clat_cfg *uc)
{
	uc->plat_prefix = cfg->base.plat_prefix;
	uc->plat_plen = cfg->base.plat_plen;
	uc->clat_prefix = cfg->base.clat_prefix;
	uc->clat_plen = cfg->base.clat_plen;
	uc->flags = cfg->base.flags & NAT64CLAT_FLAGSMASK;
	uc->set = cfg->no.set;
	strlcpy(uc->name, cfg->no.name, sizeof(uc->name));
}