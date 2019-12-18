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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_vlan_mac_obj {int /*<<< orphan*/  raw; int /*<<< orphan*/  wait; int /*<<< orphan*/  complete; int /*<<< orphan*/  restore; int /*<<< orphan*/  delete_all; struct ecore_credit_pool_obj* vlans_pool; struct ecore_credit_pool_obj* macs_pool; scalar_t__ saved_ramrod_flags; int /*<<< orphan*/  head_exe_request; scalar_t__ head_reader; int /*<<< orphan*/  head; } ;
struct ecore_credit_pool_obj {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_obj_type ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ecore_complete_vlan_mac ; 
 int /*<<< orphan*/  ecore_init_raw_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_vlan_mac_del_all ; 
 int /*<<< orphan*/  ecore_vlan_mac_restore ; 
 int /*<<< orphan*/  ecore_wait_vlan_mac ; 

__attribute__((used)) static inline void ecore_init_vlan_mac_common(struct ecore_vlan_mac_obj *o,
	uint8_t cl_id, uint32_t cid, uint8_t func_id, void *rdata, ecore_dma_addr_t rdata_mapping,
	int state, unsigned long *pstate, ecore_obj_type type,
	struct ecore_credit_pool_obj *macs_pool,
	struct ecore_credit_pool_obj *vlans_pool)
{
	ECORE_LIST_INIT(&o->head);
	o->head_reader = 0;
	o->head_exe_request = FALSE;
	o->saved_ramrod_flags = 0;

	o->macs_pool = macs_pool;
	o->vlans_pool = vlans_pool;

	o->delete_all = ecore_vlan_mac_del_all;
	o->restore = ecore_vlan_mac_restore;
	o->complete = ecore_complete_vlan_mac;
	o->wait = ecore_wait_vlan_mac;

	ecore_init_raw_obj(&o->raw, cl_id, cid, func_id, rdata, rdata_mapping,
			   state, pstate, type);
}