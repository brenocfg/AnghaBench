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
struct nl_cb {scalar_t__ cb_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  free (struct nl_cb*) ; 

void nl_cb_put(struct nl_cb *cb)
{
	if (!cb)
		return;

	cb->cb_refcnt--;

	if (cb->cb_refcnt < 0)
		BUG();

	if (cb->cb_refcnt <= 0)
		free(cb);
}