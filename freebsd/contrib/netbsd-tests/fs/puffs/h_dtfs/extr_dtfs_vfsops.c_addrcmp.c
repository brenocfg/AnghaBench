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
struct puffs_usermount {int dummy; } ;
typedef  void puffs_node ;

/* Variables and functions */

__attribute__((used)) static void *
addrcmp(struct puffs_usermount *pu, struct puffs_node *pn, void *arg)
{

	if (pn == arg)
		return pn;

	return NULL;
}