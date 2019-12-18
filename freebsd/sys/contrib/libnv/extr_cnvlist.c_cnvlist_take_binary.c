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
 scalar_t__ NV_TYPE_BINARY ; 
 int /*<<< orphan*/  nvlist_remove_nvpair (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  nvlist_report_missing (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_free_structure (void*) ; 
 scalar_t__ nvpair_get_binary (void*,size_t*) ; 
 int /*<<< orphan*/  nvpair_name (void*) ; 
 int /*<<< orphan*/ * nvpair_nvlist (void*) ; 
 scalar_t__ nvpair_type (void*) ; 

void *
cnvlist_take_binary(void *cookie, size_t *sizep)
{
	void *value;
	nvlist_t *nvl;

	if (nvpair_type(cookie) != NV_TYPE_BINARY)
		nvlist_report_missing(NV_TYPE_BINARY, nvpair_name(cookie));
	nvl = nvpair_nvlist(cookie);
	value = (void *)(intptr_t)nvpair_get_binary(cookie, sizep);
	nvlist_remove_nvpair(nvl, cookie);
	nvpair_free_structure(cookie);
	return (value);
}