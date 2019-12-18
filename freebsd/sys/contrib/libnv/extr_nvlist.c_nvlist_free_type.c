#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_6__ {scalar_t__ nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__*) ; 
 int NV_TYPE_FIRST ; 
 int NV_TYPE_LAST ; 
 int NV_TYPE_NONE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/ * nvlist_find (TYPE_1__*,int,char const*) ; 
 int /*<<< orphan*/  nvlist_free_nvpair (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_report_missing (int,char const*) ; 

void
nvlist_free_type(nvlist_t *nvl, const char *name, int type)
{
	nvpair_t *nvp;

	NVLIST_ASSERT(nvl);
	PJDLOG_ASSERT(nvl->nvl_error == 0);
	PJDLOG_ASSERT(type == NV_TYPE_NONE ||
	    (type >= NV_TYPE_FIRST && type <= NV_TYPE_LAST));

	nvp = nvlist_find(nvl, type, name);
	if (nvp != NULL)
		nvlist_free_nvpair(nvl, nvp);
	else
		nvlist_report_missing(type, name);
}