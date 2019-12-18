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
struct device_node {int dummy; } ;
struct cbe_pmd_shadow_regs {int dummy; } ;
struct cbe_regs_map {struct cbe_pmd_shadow_regs pmd_shadow_regs; } ;

/* Variables and functions */
 struct cbe_regs_map* cbe_find_map (struct device_node*) ; 

struct cbe_pmd_shadow_regs *cbe_get_pmd_shadow_regs(struct device_node *np)
{
	struct cbe_regs_map *map = cbe_find_map(np);
	if (map == NULL)
		return NULL;
	return &map->pmd_shadow_regs;
}