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
struct iser_device {int comps_used; int /*<<< orphan*/ * pd; int /*<<< orphan*/ * mr; struct iser_comp* comps; int /*<<< orphan*/  event_handler; } ;
struct iser_comp {int /*<<< orphan*/ * cq; int /*<<< orphan*/  tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ISER_VERBS ; 
 int /*<<< orphan*/  free (struct iser_comp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iser_free_device_ib_res(struct iser_device *device)
{
	int i;

	for (i = 0; i < device->comps_used; i++) {
		struct iser_comp *comp = &device->comps[i];

		taskqueue_free(comp->tq);
		ib_destroy_cq(comp->cq);
		comp->cq = NULL;
	}

	(void)ib_unregister_event_handler(&device->event_handler);
	(void)ib_dealloc_pd(device->pd);

	free(device->comps, M_ISER_VERBS);
	device->comps = NULL;

	device->mr = NULL;
	device->pd = NULL;
}