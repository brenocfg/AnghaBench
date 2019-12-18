#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nvl_error; int nvl_flags; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NVLIST_ASSERT (TYPE_1__ const*) ; 
 int NV_FLAG_PUBLIC_MASK ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 

int
nvlist_flags(const nvlist_t *nvl)
{

	NVLIST_ASSERT(nvl);
	PJDLOG_ASSERT(nvl->nvl_error == 0);

	return (nvl->nvl_flags & NV_FLAG_PUBLIC_MASK);
}