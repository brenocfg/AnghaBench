#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct netmap_slot {int buf_idx; } ;
struct netmap_mem_d {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objfree; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  netmap_free_buf (struct netmap_mem_d*,int) ; 
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* p ; 

__attribute__((used)) static void
netmap_free_bufs(struct netmap_mem_d *nmd, struct netmap_slot *slot, u_int n)
{
	u_int i;

	for (i = 0; i < n; i++) {
		if (slot[i].buf_idx > 1)
			netmap_free_buf(nmd, slot[i].buf_idx);
	}
	nm_prdis("%s: released some buffers, available: %u",
			p->name, p->objfree);
}