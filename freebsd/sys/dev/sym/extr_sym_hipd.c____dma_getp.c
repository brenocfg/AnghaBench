#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dmamap; struct TYPE_6__* next; void* baddr; void* vaddr; } ;
typedef  TYPE_1__ m_vtob_s ;
struct TYPE_7__ {int /*<<< orphan*/  dmat; int /*<<< orphan*/  nump; TYPE_1__** vtob; } ;
typedef  TYPE_2__ m_pool_s ;
typedef  void* m_addr_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int BUS_DMA_COHERENT ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int /*<<< orphan*/  MEMO_CLUSTER_SIZE ; 
 int VTOB_HASH_CODE (void*) ; 
 TYPE_1__* __sym_calloc (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  __sym_mfree (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbaddrcb ; 
 int /*<<< orphan*/  mp0 ; 

__attribute__((used)) static m_addr_t ___dma_getp(m_pool_s *mp)
{
	m_vtob_s *vbp;
	void *vaddr = NULL;
	bus_addr_t baddr = 0;

	vbp = __sym_calloc(&mp0, sizeof(*vbp), "VTOB");
	if (!vbp)
		goto out_err;

	if (bus_dmamem_alloc(mp->dmat, &vaddr,
			BUS_DMA_COHERENT | BUS_DMA_WAITOK, &vbp->dmamap))
		goto out_err;
	bus_dmamap_load(mp->dmat, vbp->dmamap, vaddr,
			MEMO_CLUSTER_SIZE, getbaddrcb, &baddr, BUS_DMA_NOWAIT);
	if (baddr) {
		int hc = VTOB_HASH_CODE(vaddr);
		vbp->vaddr = (m_addr_t) vaddr;
		vbp->baddr = (m_addr_t) baddr;
		vbp->next = mp->vtob[hc];
		mp->vtob[hc] = vbp;
		++mp->nump;
		return (m_addr_t) vaddr;
	}
out_err:
	if (baddr)
		bus_dmamap_unload(mp->dmat, vbp->dmamap);
	if (vaddr)
		bus_dmamem_free(mp->dmat, vaddr, vbp->dmamap);
	if (vbp)
		__sym_mfree(&mp0, vbp, sizeof(*vbp), "VTOB");
	return 0;
}