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
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
struct TYPE_7__ {int dt_nsegments; int /*<<< orphan*/  dt_map_count; int /*<<< orphan*/ * dt_segments; } ;
struct TYPE_6__ {int /*<<< orphan*/  dm_reslist; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 

int
sparc64_dma_alloc_map(bus_dma_tag_t dmat, bus_dmamap_t *mapp)
{

	if (dmat->dt_segments == NULL) {
		dmat->dt_segments = (bus_dma_segment_t *)malloc(
		    sizeof(bus_dma_segment_t) * dmat->dt_nsegments, M_DEVBUF,
		    M_NOWAIT);
		if (dmat->dt_segments == NULL)
			return (ENOMEM);
	}
	*mapp = malloc(sizeof(**mapp), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (*mapp == NULL)
		return (ENOMEM);

	SLIST_INIT(&(*mapp)->dm_reslist);
	dmat->dt_map_count++;
	return (0);
}