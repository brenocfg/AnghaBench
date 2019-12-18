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
struct snd_dbuf {int dmaflags; unsigned int maxsize; unsigned int bufsize; scalar_t__ buf_addr; int /*<<< orphan*/  buf; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int BUS_DMA_NOWAIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SNDBUF_F_MANAGED ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct snd_dbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sndbuf_free (struct snd_dbuf*) ; 
 int sndbuf_resize (struct snd_dbuf*,int,int) ; 
 int /*<<< orphan*/  sndbuf_setmap ; 

int
sndbuf_alloc(struct snd_dbuf *b, bus_dma_tag_t dmatag, int dmaflags,
    unsigned int size)
{
	int ret;

	b->dmatag = dmatag;
	b->dmaflags = dmaflags | BUS_DMA_NOWAIT | BUS_DMA_COHERENT;
	b->maxsize = size;
	b->bufsize = b->maxsize;
	b->buf_addr = 0;
	b->flags |= SNDBUF_F_MANAGED;
	if (bus_dmamem_alloc(b->dmatag, (void **)&b->buf, b->dmaflags,
	    &b->dmamap)) {
		sndbuf_free(b);
		return (ENOMEM);
	}
	if (bus_dmamap_load(b->dmatag, b->dmamap, b->buf, b->maxsize,
	    sndbuf_setmap, b, 0) != 0 || b->buf_addr == 0) {
		sndbuf_free(b);
		return (ENOMEM);
	}

	ret = sndbuf_resize(b, 2, b->maxsize / 2);
	if (ret != 0)
		sndbuf_free(b);

	return (ret);
}