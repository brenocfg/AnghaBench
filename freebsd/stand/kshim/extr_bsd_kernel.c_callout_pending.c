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
struct TYPE_2__ {int /*<<< orphan*/ * le_prev; } ;
struct callout {TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_callout ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
callout_pending(struct callout *c)
{
	int retval;

	mtx_lock(&mtx_callout);
	retval = (c->entry.le_prev != NULL);
	mtx_unlock(&mtx_callout);

	return (retval);
}