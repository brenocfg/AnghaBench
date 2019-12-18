#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_5__* p_subn; } ;
typedef  TYPE_2__ osm_sa_t ;
typedef  int ib_net64_t ;
struct TYPE_12__ {int* raw; } ;
struct TYPE_11__ {int /*<<< orphan*/  scope_state; TYPE_4__ mgid; } ;
typedef  TYPE_3__ ib_member_rec_t ;
typedef  TYPE_4__ ib_gid_t ;
struct TYPE_9__ {int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_13__ {TYPE_1__ opt; } ;

/* Variables and functions */
 int IB_MCR_COMPMASK_SCOPE ; 
 int IB_MC_SCOPE_LINK_LOCAL ; 
 int /*<<< orphan*/  ib_member_get_scope_state (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  osm_get_mgrp_by_mgid (TYPE_5__*,TYPE_4__*) ; 

__attribute__((used)) static unsigned build_new_mgid(osm_sa_t * sa, ib_net64_t comp_mask,
			       ib_member_rec_t * mcmr)
{
	static uint32_t uniq_count;
	ib_gid_t *mgid = &mcmr->mgid;
	uint8_t scope;
	unsigned i;

	/* use the given scope state only if requested! */
	if (comp_mask & IB_MCR_COMPMASK_SCOPE)
		ib_member_get_scope_state(mcmr->scope_state, &scope, NULL);
	else
	/* to guarantee no collision with other subnets use local scope! */
		scope = IB_MC_SCOPE_LINK_LOCAL;

	mgid->raw[0] = 0xff;
	mgid->raw[1] = 0x10 | scope;
	mgid->raw[2] = 0xa0;
	mgid->raw[3] = 0x1b;

	memcpy(&mgid->raw[4], &sa->p_subn->opt.subnet_prefix, sizeof(uint64_t));

	for (i = 0; i < 1000; i++) {
		memcpy(&mgid->raw[10], &uniq_count, 4);
		uniq_count++;
		if (!osm_get_mgrp_by_mgid(sa->p_subn, mgid))
			return 1;
	}

	return 0;
}