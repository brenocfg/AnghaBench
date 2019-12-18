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
struct nd_defrouter {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IP6NDP ; 
 int /*<<< orphan*/  free (struct nd_defrouter*,int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
defrouter_rele(struct nd_defrouter *dr)
{

	if (refcount_release(&dr->refcnt))
		free(dr, M_IP6NDP);
}