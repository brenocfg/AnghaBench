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
struct TYPE_6__ {int /*<<< orphan*/  nvl_head; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  NVPAIR_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 TYPE_1__* nvpair_nvlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

void
nvlist_remove_nvpair(nvlist_t *nvl, nvpair_t *nvp)
{

	NVLIST_ASSERT(nvl);
	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvpair_nvlist(nvp) == nvl);

	nvpair_remove(&nvl->nvl_head, nvp, nvl);
}