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
struct cv {char const* cv_description; scalar_t__ cv_waiters; } ;

/* Variables and functions */

void
cv_init(struct cv *cvp, const char *desc)
{

	cvp->cv_description = desc;
	cvp->cv_waiters = 0;
}