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
struct ecore_vlan_mac_obj {struct ecore_credit_pool_obj* vlans_pool; struct ecore_credit_pool_obj* macs_pool; } ;
struct ecore_credit_pool_obj {int /*<<< orphan*/  (* put ) (struct ecore_credit_pool_obj*,int) ;int /*<<< orphan*/  (* get ) (struct ecore_credit_pool_obj*,int) ;} ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  stub1 (struct ecore_credit_pool_obj*,int) ; 
 int /*<<< orphan*/  stub2 (struct ecore_credit_pool_obj*,int) ; 
 int /*<<< orphan*/  stub3 (struct ecore_credit_pool_obj*,int) ; 

__attribute__((used)) static bool ecore_get_credit_vlan_mac(struct ecore_vlan_mac_obj *o)
{
	struct ecore_credit_pool_obj *mp = o->macs_pool;
	struct ecore_credit_pool_obj *vp = o->vlans_pool;

	if (!mp->get(mp, 1))
		return FALSE;

	if (!vp->get(vp, 1)) {
		mp->put(mp, 1);
		return FALSE;
	}

	return TRUE;
}