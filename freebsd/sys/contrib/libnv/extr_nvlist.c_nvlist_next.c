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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * nvlist_first_nvpair (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/  const*,void*) ; 
 char const* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 

const char *
nvlist_next(const nvlist_t *nvl, int *typep, void **cookiep)
{
	nvpair_t *nvp;

	NVLIST_ASSERT(nvl);

	if (cookiep == NULL || *cookiep == NULL)
		nvp = nvlist_first_nvpair(nvl);
	else
		nvp = nvlist_next_nvpair(nvl, *cookiep);
	if (nvp == NULL)
		return (NULL);
	if (typep != NULL)
		*typep = nvpair_type(nvp);
	if (cookiep != NULL)
		*cookiep = nvp;
	return (nvpair_name(nvp));
}