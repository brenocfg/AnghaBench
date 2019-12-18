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
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;
struct pvscsi_softc {int /*<<< orphan*/  dev; } ;
struct pvscsi_dma {size_t paddr; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pvscsi_dma_alloc (struct pvscsi_softc*,struct pvscsi_dma*,size_t,size_t) ; 

__attribute__((used)) static int
pvscsi_dma_alloc_ppns(struct pvscsi_softc *sc, struct pvscsi_dma *dma,
    uint64_t *ppn_list, uint32_t num_pages)
{
	int error;
	uint32_t i;
	uint64_t ppn;

	error = pvscsi_dma_alloc(sc, dma, num_pages * PAGE_SIZE, PAGE_SIZE);
	if (error) {
		device_printf(sc->dev, "Error allocating pages, error %d\n",
		    error);
		return (error);
	}

	ppn = dma->paddr >> PAGE_SHIFT;
	for (i = 0; i < num_pages; i++) {
		ppn_list[i] = ppn + i;
	}

	return (0);
}