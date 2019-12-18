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
struct TYPE_4__ {struct TYPE_4__* lc_cap; struct TYPE_4__* lc_class; struct TYPE_4__* lc_style; } ;
typedef  TYPE_1__ login_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
mm_login_close(login_cap_t *lc)
{
	if (lc == NULL)
		return;
	free(lc->lc_style);
	free(lc->lc_class);
	free(lc->lc_cap);
	free(lc);
}