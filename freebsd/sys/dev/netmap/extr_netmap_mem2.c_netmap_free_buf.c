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
typedef  int uint32_t ;
struct netmap_obj_pool {int objtotal; } ;
struct netmap_mem_d {struct netmap_obj_pool* pools; } ;

/* Variables and functions */
 size_t NETMAP_BUF_POOL ; 
 int /*<<< orphan*/  netmap_obj_free (struct netmap_obj_pool*,int) ; 
 int /*<<< orphan*/  nm_prerr (char*,int,int) ; 

__attribute__((used)) static void
netmap_free_buf(struct netmap_mem_d *nmd, uint32_t i)
{
	struct netmap_obj_pool *p = &nmd->pools[NETMAP_BUF_POOL];

	if (i < 2 || i >= p->objtotal) {
		nm_prerr("Cannot free buf#%d: should be in [2, %d[", i, p->objtotal);
		return;
	}
	netmap_obj_free(p, i);
}