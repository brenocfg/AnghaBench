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
struct nm_bridge {char const* bdg_basename; } ;
struct netmap_vp_adapter {struct nm_bridge* na_bdg; } ;

/* Variables and functions */

const char*
netmap_bdg_name(struct netmap_vp_adapter *vp)
{
	struct nm_bridge *b = vp->na_bdg;
	if (b == NULL)
		return NULL;
	return b->bdg_basename;
}