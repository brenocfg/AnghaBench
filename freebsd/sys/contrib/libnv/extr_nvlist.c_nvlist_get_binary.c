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
 int /*<<< orphan*/  NV_TYPE_BINARY ; 
 int /*<<< orphan*/ * nvlist_find (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  nvlist_report_missing (int /*<<< orphan*/ ,char const*) ; 
 void const* nvpair_get_binary (int /*<<< orphan*/ *,size_t*) ; 

const void *
nvlist_get_binary(const nvlist_t *nvl, const char *name, size_t *sizep)
{
	nvpair_t *nvp;

	nvp = nvlist_find(nvl, NV_TYPE_BINARY, name);
	if (nvp == NULL)
		nvlist_report_missing(NV_TYPE_BINARY, name);

	return (nvpair_get_binary(nvp, sizep));
}