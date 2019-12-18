#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nvl_error; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 

void
nvlist_set_error(nvlist_t *nvl, int error)
{

	PJDLOG_ASSERT(error != 0);

	/*
	 * Check for error != 0 so that we don't do the wrong thing if somebody
	 * tries to abuse this API when asserts are disabled.
	 */
	if (nvl != NULL && error != 0 && nvl->nvl_error == 0)
		nvl->nvl_error = error;
}