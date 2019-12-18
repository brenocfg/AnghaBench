#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_5__ {int /*<<< orphan*/  m; TYPE_1__ si; int /*<<< orphan*/ * ntfytq; int /*<<< orphan*/  ntfytask; } ;
typedef  TYPE_2__ NM_SELINFO_T ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  knlist_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

void
nm_os_selinfo_uninit(NM_SELINFO_T *si)
{
	if (si->ntfytq == NULL) {
		return;	/* si was not initialized */
	}
	taskqueue_drain(si->ntfytq, &si->ntfytask);
	taskqueue_free(si->ntfytq);
	si->ntfytq = NULL;
	knlist_delete(&si->si.si_note, curthread, /*islocked=*/0);
	knlist_destroy(&si->si.si_note);
	/* now we don't need the mutex anymore */
	mtx_destroy(&si->m);
}