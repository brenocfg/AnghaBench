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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
struct netmap_slot {int /*<<< orphan*/  buf_idx; scalar_t__ ptr; scalar_t__ flags; int /*<<< orphan*/  len; } ;
struct netmap_obj_pool {int /*<<< orphan*/  objfree; int /*<<< orphan*/  name; int /*<<< orphan*/  _objsize; } ;
struct netmap_mem_d {struct netmap_obj_pool* pools; } ;
typedef  int /*<<< orphan*/  slot ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NETMAP_BUF_POOL ; 
 int /*<<< orphan*/  bzero (struct netmap_slot*,size_t) ; 
 void* netmap_buf_malloc (struct netmap_mem_d*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_obj_free (struct netmap_obj_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prerr (char*,size_t,size_t) ; 

__attribute__((used)) static int
netmap_new_bufs(struct netmap_mem_d *nmd, struct netmap_slot *slot, u_int n)
{
	struct netmap_obj_pool *p = &nmd->pools[NETMAP_BUF_POOL];
	u_int i = 0;	/* slot counter */
	uint32_t pos = 0;	/* slot in p->bitmap */
	uint32_t index = 0;	/* buffer index */

	for (i = 0; i < n; i++) {
		void *vaddr = netmap_buf_malloc(nmd, &pos, &index);
		if (vaddr == NULL) {
			nm_prerr("no more buffers after %d of %d", i, n);
			goto cleanup;
		}
		slot[i].buf_idx = index;
		slot[i].len = p->_objsize;
		slot[i].flags = 0;
		slot[i].ptr = 0;
	}

	nm_prdis("%s: allocated %d buffers, %d available, first at %d", p->name, n, p->objfree, pos);
	return (0);

cleanup:
	while (i > 0) {
		i--;
		netmap_obj_free(p, slot[i].buf_idx);
	}
	bzero(slot, n * sizeof(slot[0]));
	return (ENOMEM);
}