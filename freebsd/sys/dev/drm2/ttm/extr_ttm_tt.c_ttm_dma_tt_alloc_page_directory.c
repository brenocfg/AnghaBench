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
struct TYPE_2__ {int num_pages; void* pages; } ;
struct ttm_dma_tt {TYPE_1__ ttm; void* dma_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_PD ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ttm_dma_tt_alloc_page_directory(struct ttm_dma_tt *ttm)
{
	ttm->ttm.pages = malloc(ttm->ttm.num_pages * sizeof(void *),
	    M_TTM_PD, M_WAITOK | M_ZERO);
	ttm->dma_address = malloc(ttm->ttm.num_pages *
	    sizeof(*ttm->dma_address), M_TTM_PD, M_WAITOK);
}