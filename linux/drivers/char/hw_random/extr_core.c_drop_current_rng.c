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
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cleanup_rng ; 
 TYPE_1__* current_rng ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rng_mutex ; 

__attribute__((used)) static void drop_current_rng(void)
{
	BUG_ON(!mutex_is_locked(&rng_mutex));
	if (!current_rng)
		return;

	/* decrease last reference for triggering the cleanup */
	kref_put(&current_rng->ref, cleanup_rng);
	current_rng = NULL;
}