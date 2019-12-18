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
struct chunk {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  alloc_addr; int /*<<< orphan*/  alloc_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fore200e_dma_chunk_free(struct fore200e* fore200e, struct chunk* chunk)
{
	dma_free_coherent(fore200e->dev, chunk->alloc_size, chunk->alloc_addr,
			  chunk->dma_addr);
}