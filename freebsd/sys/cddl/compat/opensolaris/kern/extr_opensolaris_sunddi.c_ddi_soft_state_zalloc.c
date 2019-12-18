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
struct ddi_soft_state_item {int ssi_item; struct ddi_soft_state_item* ssi_data; } ;
struct ddi_soft_state {int ss_size; int /*<<< orphan*/  ss_lock; int /*<<< orphan*/  ss_list; } ;

/* Variables and functions */
 int DDI_FAILURE ; 
 int DDI_SUCCESS ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ddi_soft_state_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ddi_get_soft_state_locked (struct ddi_soft_state*,int) ; 
 struct ddi_soft_state_item* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (struct ddi_soft_state_item*,int) ; 
 struct ddi_soft_state_item* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_next ; 

int
ddi_soft_state_zalloc(void *state, int item)
{
	struct ddi_soft_state *ss = state;
	struct ddi_soft_state_item *itemp;

	itemp = kmem_alloc(sizeof(*itemp), KM_SLEEP);
	itemp->ssi_item = item;
	itemp->ssi_data = kmem_zalloc(ss->ss_size, KM_SLEEP);

	mutex_enter(&ss->ss_lock);
	if (ddi_get_soft_state_locked(ss, item) != NULL) {
		mutex_exit(&ss->ss_lock);
		kmem_free(itemp->ssi_data, ss->ss_size);
		kmem_free(itemp, sizeof(*itemp));
		return (DDI_FAILURE);
	}
	LIST_INSERT_HEAD(&ss->ss_list, itemp, ssi_next);
	mutex_exit(&ss->ss_lock);
	return (DDI_SUCCESS);
}