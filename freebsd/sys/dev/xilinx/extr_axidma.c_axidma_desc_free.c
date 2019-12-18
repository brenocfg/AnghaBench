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
struct xdma_channel {int /*<<< orphan*/  vmem; } ;
struct axidma_softc {int dummy; } ;
struct axidma_channel {int descs_num; int /*<<< orphan*/  mem_size; int /*<<< orphan*/  mem_paddr; int /*<<< orphan*/  mem_vaddr; int /*<<< orphan*/  descs_phys; int /*<<< orphan*/  descs; struct xdma_channel* xchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kva_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kremove_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
axidma_desc_free(struct axidma_softc *sc, struct axidma_channel *chan)
{
	struct xdma_channel *xchan;
	int nsegments;

	nsegments = chan->descs_num;
	xchan = chan->xchan;

	free(chan->descs, M_DEVBUF);
	free(chan->descs_phys, M_DEVBUF);

	pmap_kremove_device(chan->mem_vaddr, chan->mem_size);
	kva_free(chan->mem_vaddr, chan->mem_size);
	vmem_free(xchan->vmem, chan->mem_paddr, chan->mem_size);

	return (0);
}