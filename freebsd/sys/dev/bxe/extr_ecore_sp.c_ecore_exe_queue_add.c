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
struct ecore_exeq_elem {int /*<<< orphan*/  link; } ;
struct ecore_exe_queue_obj {int (* optimize ) (struct bxe_softc*,int /*<<< orphan*/ ,struct ecore_exeq_elem*) ;int (* validate ) (struct bxe_softc*,int /*<<< orphan*/ ,struct ecore_exeq_elem*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  exe_queue; int /*<<< orphan*/  owner; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_LIST_PUSH_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  ECORE_SPIN_LOCK_BH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_SPIN_UNLOCK_BH (int /*<<< orphan*/ *) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ecore_exe_queue_free_elem (struct bxe_softc*,struct ecore_exeq_elem*) ; 
 int stub1 (struct bxe_softc*,int /*<<< orphan*/ ,struct ecore_exeq_elem*) ; 
 int stub2 (struct bxe_softc*,int /*<<< orphan*/ ,struct ecore_exeq_elem*) ; 

__attribute__((used)) static inline int ecore_exe_queue_add(struct bxe_softc *sc,
				      struct ecore_exe_queue_obj *o,
				      struct ecore_exeq_elem *elem,
				      bool restore)
{
	int rc;

	ECORE_SPIN_LOCK_BH(&o->lock);

	if (!restore) {
		/* Try to cancel this element queue */
		rc = o->optimize(sc, o->owner, elem);
		if (rc)
			goto free_and_exit;

		/* Check if this request is ok */
		rc = o->validate(sc, o->owner, elem);
		if (rc) {
			ECORE_MSG(sc, "Preamble failed: %d\n", rc);
			goto free_and_exit;
		}
	}

	/* If so, add it to the execution queue */
	ECORE_LIST_PUSH_TAIL(&elem->link, &o->exe_queue);

	ECORE_SPIN_UNLOCK_BH(&o->lock);

	return ECORE_SUCCESS;

free_and_exit:
	ecore_exe_queue_free_elem(sc, elem);

	ECORE_SPIN_UNLOCK_BH(&o->lock);

	return rc;
}