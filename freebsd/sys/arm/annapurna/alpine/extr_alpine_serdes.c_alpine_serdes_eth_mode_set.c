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
typedef  size_t uint32_t ;
struct alpine_serdes_eth_group_mode {int mode_set; int mode; int /*<<< orphan*/  lock; } ;
struct al_serdes_grp_obj {int /*<<< orphan*/  (* mode_set_kr ) (struct al_serdes_grp_obj*) ;int /*<<< orphan*/  (* mode_set_sgmii ) (struct al_serdes_grp_obj*) ;} ;
typedef  enum alpine_serdes_eth_mode { ____Placeholder_alpine_serdes_eth_mode } alpine_serdes_eth_mode ;

/* Variables and functions */
 int ALPINE_SERDES_ETH_MODE_SGMII ; 
 int EINVAL ; 
 size_t SERDES_NUM_GROUPS ; 
 int /*<<< orphan*/  al_serdes_handle_grp_init (int /*<<< orphan*/ ,size_t,struct al_serdes_grp_obj*) ; 
 struct alpine_serdes_eth_group_mode* alpine_serdes_eth_group_mode ; 
 int /*<<< orphan*/  alpine_serdes_resource_get (size_t) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serdes_base ; 
 int /*<<< orphan*/  stub1 (struct al_serdes_grp_obj*) ; 
 int /*<<< orphan*/  stub2 (struct al_serdes_grp_obj*) ; 

int
alpine_serdes_eth_mode_set(uint32_t group, enum alpine_serdes_eth_mode mode)
{
	struct alpine_serdes_eth_group_mode *group_mode;

	group_mode = &alpine_serdes_eth_group_mode[group];

	if (serdes_base == NULL)
		return (EINVAL);

	if (group >= SERDES_NUM_GROUPS)
		return (EINVAL);

	mtx_lock(&group_mode->lock);

	if (!group_mode->mode_set || (group_mode->mode != mode)) {
		struct al_serdes_grp_obj obj;

		al_serdes_handle_grp_init(alpine_serdes_resource_get(group),
		    group, &obj);

		if (mode == ALPINE_SERDES_ETH_MODE_SGMII)
			obj.mode_set_sgmii(&obj);
		else
			obj.mode_set_kr(&obj);

		group_mode->mode = mode;
		group_mode->mode_set = true;
	}

	mtx_unlock(&group_mode->lock);

	return (0);
}