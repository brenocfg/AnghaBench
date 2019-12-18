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
struct TYPE_4__ {scalar_t__ cs_flags; int /*<<< orphan*/  cs_ch; } ;
typedef  TYPE_1__ VCS ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  ISBLANK (int /*<<< orphan*/ ) ; 
 scalar_t__ cs_next (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
cs_fspace(SCR *sp, VCS *csp)
{
	if (csp->cs_flags != 0 || !ISBLANK(csp->cs_ch))
		return (0);
	for (;;) {
		if (cs_next(sp, csp))
			return (1);
		if (csp->cs_flags != 0 || !ISBLANK(csp->cs_ch))
			break;
	}
	return (0);
}