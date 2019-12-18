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
struct llentry {scalar_t__ r_skip_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLE_REQ_LOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_UNLOCK (struct llentry*) ; 

__attribute__((used)) static void
in_lltable_mark_used(struct llentry *lle)
{

	LLE_REQ_LOCK(lle);
	lle->r_skip_req = 0;
	LLE_REQ_UNLOCK(lle);
}