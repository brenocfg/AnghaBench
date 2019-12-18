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

/* Variables and functions */
 int /*<<< orphan*/ * nvlist_get_array_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* nvlist_get_parent (int /*<<< orphan*/  const*,void**) ; 

const nvlist_t *
nvlist_get_pararr(const nvlist_t *nvl, void **cookiep)
{
	const nvlist_t *ret;

	ret = nvlist_get_array_next(nvl);
	if (ret != NULL) {
		if (cookiep != NULL)
			*cookiep = NULL;
		return (ret);
	}

	return (nvlist_get_parent(nvl, cookiep));
}