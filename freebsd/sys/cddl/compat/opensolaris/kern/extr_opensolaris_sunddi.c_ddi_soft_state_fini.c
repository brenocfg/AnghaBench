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
struct ddi_soft_state_item {int ssi_item; } ;
struct ddi_soft_state {int /*<<< orphan*/  ss_lock; int /*<<< orphan*/  ss_list; } ;

/* Variables and functions */
 struct ddi_soft_state_item* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddi_soft_state_free_locked (struct ddi_soft_state*,int) ; 
 int /*<<< orphan*/  kmem_free (struct ddi_soft_state*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
ddi_soft_state_fini(void **statep)
{
	struct ddi_soft_state *ss = *statep;
	struct ddi_soft_state_item *itemp;
	int item;

	mutex_enter(&ss->ss_lock);
	while ((itemp = LIST_FIRST(&ss->ss_list)) != NULL) {
		item = itemp->ssi_item;
		ddi_soft_state_free_locked(ss, item);
	}
	mutex_exit(&ss->ss_lock);
	mutex_destroy(&ss->ss_lock);
	kmem_free(ss, sizeof(*ss));

	*statep = NULL;
}