#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bus_dma_tag_t ;
struct TYPE_4__ {scalar_t__ dt_map_count; scalar_t__ dt_ref_count; struct TYPE_4__* dt_segments; struct TYPE_4__* dt_parent; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  atomic_subtract_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
bus_dma_tag_destroy(bus_dma_tag_t dmat)
{
	bus_dma_tag_t parent;

	if (dmat != NULL) {
		if (dmat->dt_map_count != 0)
			return (EBUSY);
		while (dmat != NULL) {
			parent = dmat->dt_parent;
			atomic_subtract_int(&dmat->dt_ref_count, 1);
			if (dmat->dt_ref_count == 0) {
				if (dmat->dt_segments != NULL)
					free(dmat->dt_segments, M_DEVBUF);
				free(dmat, M_DEVBUF);
				/*
				 * Last reference count, so
				 * release our reference
				 * count on our parent.
				 */
				dmat = parent;
			} else
				dmat = NULL;
		}
	}
	return (0);
}