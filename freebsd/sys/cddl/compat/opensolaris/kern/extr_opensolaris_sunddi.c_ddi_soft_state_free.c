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
struct ddi_soft_state {int /*<<< orphan*/  ss_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddi_soft_state_free_locked (struct ddi_soft_state*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
ddi_soft_state_free(void *state, int item)
{
	struct ddi_soft_state *ss = state;

	mutex_enter(&ss->ss_lock);
	ddi_soft_state_free_locked(ss, item);
	mutex_exit(&ss->ss_lock);
}