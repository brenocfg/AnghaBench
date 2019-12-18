#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  set; } ;
struct nptv6_cfg {int flags; TYPE_1__ no; int /*<<< orphan*/  plen; int /*<<< orphan*/  external; int /*<<< orphan*/  if_name; int /*<<< orphan*/  internal; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  set; int /*<<< orphan*/  plen; int /*<<< orphan*/  external; int /*<<< orphan*/  if_name; int /*<<< orphan*/  internal; } ;
typedef  TYPE_2__ ipfw_nptv6_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  IF_NAMESIZE ; 
 int NPTV6_DYNAMIC_PREFIX ; 
 int NPTV6_FLAGSMASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nptv6_export_config(struct ip_fw_chain *ch, struct nptv6_cfg *cfg,
    ipfw_nptv6_cfg *uc)
{

	uc->internal = cfg->internal;
	if (cfg->flags & NPTV6_DYNAMIC_PREFIX)
		memcpy(uc->if_name, cfg->if_name, IF_NAMESIZE);
	else
		uc->external = cfg->external;
	uc->plen = cfg->plen;
	uc->flags = cfg->flags & NPTV6_FLAGSMASK;
	uc->set = cfg->no.set;
	strlcpy(uc->name, cfg->no.name, sizeof(uc->name));
}