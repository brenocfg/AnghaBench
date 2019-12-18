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
 int /*<<< orphan*/  NVLIST_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVPAIR_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  nvlist_remove_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvpair_nvlist (int /*<<< orphan*/ *) ; 

void
nvlist_free_nvpair(nvlist_t *nvl, nvpair_t *nvp)
{

	NVLIST_ASSERT(nvl);
	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvpair_nvlist(nvp) == nvl);

	nvlist_remove_nvpair(nvl, nvp);
	nvpair_free(nvp);
}