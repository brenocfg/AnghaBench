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
typedef  int u_int32_t ;
struct emu_mem {int* bmap; int* ptb_pages; int /*<<< orphan*/  blocks; } ;
struct sc_info {struct emu_mem mem; } ;
struct emu_memblk {int buf; int pte_start; int pte_size; scalar_t__ buf_addr; int /*<<< orphan*/  buf_map; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int EMUMAXPAGES ; 
 int EMUPAGESIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct emu_memblk*,int /*<<< orphan*/ ) ; 
 void* emu_malloc (struct sc_info*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct emu_memblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct emu_memblk* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 

__attribute__((used)) static void *
emu_memalloc(struct sc_info *sc, u_int32_t sz, bus_addr_t *addr)
{
	u_int32_t blksz, start, idx, ofs, tmp, found;
	struct emu_mem *mem = &sc->mem;
	struct emu_memblk *blk;
	void *buf;

	blksz = sz / EMUPAGESIZE;
	if (sz > (blksz * EMUPAGESIZE))
		blksz++;
	/* find a free block in the bitmap */
	found = 0;
	start = 1;
	while (!found && start + blksz < EMUMAXPAGES) {
		found = 1;
		for (idx = start; idx < start + blksz; idx++)
			if (mem->bmap[idx >> 3] & (1 << (idx & 7)))
				found = 0;
		if (!found)
			start++;
	}
	if (!found)
		return NULL;
	blk = malloc(sizeof(*blk), M_DEVBUF, M_NOWAIT);
	if (blk == NULL)
		return NULL;
	buf = emu_malloc(sc, sz, &blk->buf_addr, &blk->buf_map);
	*addr = blk->buf_addr;
	if (buf == NULL) {
		free(blk, M_DEVBUF);
		return NULL;
	}
	blk->buf = buf;
	blk->pte_start = start;
	blk->pte_size = blksz;
#ifdef EMUDEBUG
	printf("buf %p, pte_start %d, pte_size %d\n", blk->buf,
	    blk->pte_start, blk->pte_size);
#endif
	ofs = 0;
	for (idx = start; idx < start + blksz; idx++) {
		mem->bmap[idx >> 3] |= 1 << (idx & 7);
		tmp = (uint32_t)(blk->buf_addr + ofs);
#ifdef EMUDEBUG
		printf("pte[%d] -> %x phys, %x virt\n", idx, tmp,
		    ((u_int32_t)buf) + ofs);
#endif
		mem->ptb_pages[idx] = (tmp << 1) | idx;
		ofs += EMUPAGESIZE;
	}
	SLIST_INSERT_HEAD(&mem->blocks, blk, link);
	return buf;
}