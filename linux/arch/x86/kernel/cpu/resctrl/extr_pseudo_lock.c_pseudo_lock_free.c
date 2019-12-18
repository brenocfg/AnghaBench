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
struct rdtgroup {int /*<<< orphan*/ * plr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseudo_lock_region_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pseudo_lock_free(struct rdtgroup *rdtgrp)
{
	pseudo_lock_region_clear(rdtgrp->plr);
	kfree(rdtgrp->plr);
	rdtgrp->plr = NULL;
}