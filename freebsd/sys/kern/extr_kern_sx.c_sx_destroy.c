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
struct sx {scalar_t__ sx_lock; scalar_t__ sx_recurse; int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SX_LOCK_DESTROYED ; 
 scalar_t__ SX_LOCK_UNLOCKED ; 
 int /*<<< orphan*/  lock_destroy (int /*<<< orphan*/ *) ; 

void
sx_destroy(struct sx *sx)
{

	KASSERT(sx->sx_lock == SX_LOCK_UNLOCKED, ("sx lock still held"));
	KASSERT(sx->sx_recurse == 0, ("sx lock still recursed"));
	sx->sx_lock = SX_LOCK_DESTROYED;
	lock_destroy(&sx->lock_object);
}