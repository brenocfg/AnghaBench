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
struct gsw_mt753x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt753x_apply_vlan_config (struct gsw_mt753x*) ; 

__attribute__((used)) static inline int mt753x_swconfig_init(struct gsw_mt753x *gsw)
{
	mt753x_apply_vlan_config(gsw);

	return 0;
}