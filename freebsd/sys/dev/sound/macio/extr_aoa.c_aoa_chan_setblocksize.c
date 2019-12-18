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
typedef  int u_int32_t ;
struct aoa_dma {int blksz; int bufsz; int /*<<< orphan*/  channel; int /*<<< orphan*/  buf; int /*<<< orphan*/  running; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  aoa_dma_set_program (struct aoa_dma*) ; 
 int dbdma_resize_channel (int /*<<< orphan*/ ,int) ; 
 int sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
aoa_chan_setblocksize(kobj_t obj, void *data, u_int32_t blocksz)
{
	struct aoa_dma 		*dma = data;
	int 			 err, lz;

	DPRINTF(("aoa_chan_setblocksize: blocksz = %u, dma->blksz = %u\n", 
		blocksz, dma->blksz));
	KASSERT(!dma->running, ("dma is running"));
	KASSERT(blocksz > 0, ("bad blocksz"));

	/* Round blocksz down to a power of two... */
	__asm volatile ("cntlzw %0,%1" : "=r"(lz) : "r"(blocksz));
	blocksz = 1 << (31 - lz);
	DPRINTF(("blocksz = %u\n", blocksz));

	/* ...but no more than the buffer. */
	if (blocksz > dma->bufsz)
		blocksz = dma->bufsz;

	err = sndbuf_resize(dma->buf, dma->bufsz / blocksz, blocksz);
	if (err != 0) {
		DPRINTF(("sndbuf_resize returned %d\n", err));
		return (0);
	}

	if (blocksz == dma->blksz)
		return (dma->blksz);

	/* One slot per block plus branch to 0 plus STOP. */
	err = dbdma_resize_channel(dma->channel, 2 + dma->bufsz / blocksz);
	if (err != 0) {
		DPRINTF(("dbdma_resize_channel returned %d\n", err));
		return (0);
	}

	/* Set the new blocksize. */
	dma->blksz = blocksz;
	aoa_dma_set_program(dma);

	return (dma->blksz);
}