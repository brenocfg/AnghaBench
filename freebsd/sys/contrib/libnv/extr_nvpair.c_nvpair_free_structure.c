#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nvp_magic; int /*<<< orphan*/ * nvp_list; } ;
typedef  TYPE_1__ nvpair_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVPAIR_ASSERT (TYPE_1__*) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_free (TYPE_1__*) ; 

void
nvpair_free_structure(nvpair_t *nvp)
{

	NVPAIR_ASSERT(nvp);
	PJDLOG_ASSERT(nvp->nvp_list == NULL);

	nvp->nvp_magic = 0;
	nv_free(nvp);
}