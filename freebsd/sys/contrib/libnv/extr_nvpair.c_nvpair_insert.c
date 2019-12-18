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
struct nvl_head {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * nvp_list; } ;
typedef  TYPE_1__ nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__*) ; 
 int NV_FLAG_NO_UNIQUE ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct nvl_head*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nvlist_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvp_next ; 
 int /*<<< orphan*/  nvpair_name (TYPE_1__*) ; 

void
nvpair_insert(struct nvl_head *head, nvpair_t *nvp, nvlist_t *nvl)
{

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_list == NULL);
	PJDLOG_ASSERT((nvlist_flags(nvl) & NV_FLAG_NO_UNIQUE) != 0 ||
	    !nvlist_exists(nvl, nvpair_name(nvp)));

	TAILQ_INSERT_TAIL(head, nvp, nvp_next);
	nvp->nvp_list = nvl;
}