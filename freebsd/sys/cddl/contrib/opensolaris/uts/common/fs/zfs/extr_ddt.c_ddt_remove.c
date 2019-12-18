#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ddt_tree; int /*<<< orphan*/  ddt_lock; } ;
typedef  TYPE_1__ ddt_t ;
typedef  int /*<<< orphan*/  ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_free (int /*<<< orphan*/ *) ; 

void
ddt_remove(ddt_t *ddt, ddt_entry_t *dde)
{
	ASSERT(MUTEX_HELD(&ddt->ddt_lock));

	avl_remove(&ddt->ddt_tree, dde);
	ddt_free(dde);
}