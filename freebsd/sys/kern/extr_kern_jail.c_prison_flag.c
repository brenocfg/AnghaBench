#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {TYPE_1__* cr_prison; } ;
struct TYPE_2__ {unsigned int pr_flags; } ;

/* Variables and functions */

int
prison_flag(struct ucred *cred, unsigned flag)
{

	/* This is an atomic read, so no locking is necessary. */
	return (cred->cr_prison->pr_flags & flag);
}