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
struct bcma_devinfo {int rid_agent; int /*<<< orphan*/  resources; scalar_t__ num_intrs; int /*<<< orphan*/  intrs; int /*<<< orphan*/ * res_agent; int /*<<< orphan*/ * corecfg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct bcma_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

struct bcma_devinfo *
bcma_alloc_dinfo(device_t bus)
{
	struct bcma_devinfo *dinfo;
	
	dinfo = malloc(sizeof(struct bcma_devinfo), M_BHND, M_NOWAIT|M_ZERO);
	if (dinfo == NULL)
		return (NULL);

	dinfo->corecfg = NULL;
	dinfo->res_agent = NULL;
	dinfo->rid_agent = -1;

	STAILQ_INIT(&dinfo->intrs);
	dinfo->num_intrs = 0;

	resource_list_init(&dinfo->resources);

	return (dinfo);
}