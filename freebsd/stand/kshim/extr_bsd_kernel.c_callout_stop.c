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
struct callout {int /*<<< orphan*/ * c_arg; int /*<<< orphan*/ * c_func; TYPE_1__ entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct callout*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  mtx_callout ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
callout_stop(struct callout *c)
{
	mtx_lock(&mtx_callout);

	if (c->entry.le_prev != NULL) {
		LIST_REMOVE(c, entry);
		c->entry.le_prev = NULL;
	}
	mtx_unlock(&mtx_callout);

	c->c_func = NULL;
	c->c_arg = NULL;
}