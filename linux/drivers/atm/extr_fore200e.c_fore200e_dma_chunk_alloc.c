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
struct fore200e {int /*<<< orphan*/  dev; } ;
struct chunk {int alloc_size; scalar_t__ alloc_addr; scalar_t__ align_addr; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fore200e_dma_chunk_alloc(struct fore200e *fore200e, struct chunk *chunk,
		int size, int nbr, int alignment)
{
	/* returned chunks are page-aligned */
	chunk->alloc_size = size * nbr;
	chunk->alloc_addr = dma_alloc_coherent(fore200e->dev, chunk->alloc_size,
					       &chunk->dma_addr, GFP_KERNEL);
	if (!chunk->alloc_addr)
		return -ENOMEM;
	chunk->align_addr = chunk->alloc_addr;
	return 0;
}