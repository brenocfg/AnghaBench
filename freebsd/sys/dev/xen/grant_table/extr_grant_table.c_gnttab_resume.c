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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 unsigned int PAGE_SIZE ; 
 int gnttab_map (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * gnttab_pseudo_phys_res ; 
 int /*<<< orphan*/  gnttab_pseudo_phys_res_id ; 
 unsigned int max_nr_grant_frames () ; 
 unsigned int nr_grant_frames ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ resume_frames ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xenmem_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

int
gnttab_resume(device_t dev)
{
	unsigned int max_nr_gframes, nr_gframes;

	nr_gframes = nr_grant_frames;
	max_nr_gframes = max_nr_grant_frames();
	if (max_nr_gframes < nr_gframes)
		return (ENOSYS);

	if (!resume_frames) {
		KASSERT(dev != NULL,
		    ("No resume frames and no device provided"));

		gnttab_pseudo_phys_res = xenmem_alloc(dev,
		    &gnttab_pseudo_phys_res_id, PAGE_SIZE * max_nr_gframes);
		if (gnttab_pseudo_phys_res == NULL)
			panic("Unable to reserve physical memory for gnttab");
		resume_frames = rman_get_start(gnttab_pseudo_phys_res);
	}

	return (gnttab_map(0, nr_gframes - 1));
}