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
struct plimit {int /*<<< orphan*/  pl_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PLIMIT ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
lim_free(struct plimit *limp)
{

	if (refcount_release(&limp->pl_refcnt))
		free((void *)limp, M_PLIMIT);
}