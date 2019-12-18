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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fds ;

/* Variables and functions */
 int* nv_malloc (int) ; 
 size_t nvlist_ndescriptors (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nvlist_xdescriptors (int /*<<< orphan*/  const*,int*) ; 

int *
nvlist_descriptors(const nvlist_t *nvl, size_t *nitemsp)
{
	size_t nitems;
	int *fds;

	nitems = nvlist_ndescriptors(nvl);
	fds = nv_malloc(sizeof(fds[0]) * (nitems + 1));
	if (fds == NULL)
		return (NULL);
	if (nitems > 0)
		nvlist_xdescriptors(nvl, fds);
	fds[nitems] = -1;
	if (nitemsp != NULL)
		*nitemsp = nitems;
	return (fds);
}