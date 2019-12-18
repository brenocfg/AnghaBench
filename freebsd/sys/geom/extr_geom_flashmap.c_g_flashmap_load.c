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
struct g_provider {int /*<<< orphan*/  name; } ;
struct g_flashmap_slice {scalar_t__ sl_end; scalar_t__ sl_start; int /*<<< orphan*/  sl_name; } ;
struct g_flashmap_head {int dummy; } ;
struct flash_slice {scalar_t__ size; scalar_t__ base; int /*<<< orphan*/  label; } ;
typedef  scalar_t__ (* flash_slicer_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flash_slice*,int*) ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FLASH_SLICES_MAX_NUM ; 
 int /*<<< orphan*/  M_FLASHMAP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct g_flashmap_head*,struct g_flashmap_slice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct flash_slice*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sl_link ; 

__attribute__((used)) static int
g_flashmap_load(device_t dev, struct g_provider *pp, flash_slicer_t slicer,
    struct g_flashmap_head *head)
{
	struct flash_slice *slices;
	struct g_flashmap_slice *slice;
	int i, nslices = 0;

	slices = malloc(sizeof(struct flash_slice) * FLASH_SLICES_MAX_NUM,
	    M_FLASHMAP, M_WAITOK | M_ZERO);
	if (slicer(dev, pp->name, slices, &nslices) == 0) {
		for (i = 0; i < nslices; i++) {
			slice = malloc(sizeof(struct g_flashmap_slice),
			    M_FLASHMAP, M_WAITOK);

			slice->sl_name = slices[i].label;
			slice->sl_start = slices[i].base;
			slice->sl_end = slices[i].base + slices[i].size - 1;

			STAILQ_INSERT_TAIL(head, slice, sl_link);
		}
	}

	free(slices, M_FLASHMAP);
	return (nslices);
}