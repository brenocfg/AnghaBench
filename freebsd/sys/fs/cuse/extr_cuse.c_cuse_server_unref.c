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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct cuse_server_dev {scalar_t__ refs; int /*<<< orphan*/  cv; TYPE_1__ selinfo; int /*<<< orphan*/  hmem; int /*<<< orphan*/  hdev; } ;
struct cuse_server {scalar_t__ refs; int /*<<< orphan*/  cv; TYPE_1__ selinfo; int /*<<< orphan*/  hmem; int /*<<< orphan*/  hdev; } ;
struct cuse_memory {scalar_t__ refs; int /*<<< orphan*/  cv; TYPE_1__ selinfo; int /*<<< orphan*/  hmem; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CUSE ; 
 struct cuse_server_dev* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cuse_server_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_free_unit_by_id_locked (struct cuse_server_dev*,int) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_server_free_dev (struct cuse_server_dev*) ; 
 int /*<<< orphan*/  cuse_server_head ; 
 int /*<<< orphan*/  cuse_server_is_closing (struct cuse_server_dev*) ; 
 int /*<<< orphan*/  cuse_server_wakeup_all_client_locked (struct cuse_server_dev*) ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  cuse_vm_memory_free (struct cuse_server_dev*) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct cuse_server_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static void
cuse_server_unref(struct cuse_server *pcs)
{
	struct cuse_server_dev *pcsd;
	struct cuse_memory *mem;

	cuse_lock();
	pcs->refs--;
	if (pcs->refs != 0) {
		cuse_unlock();
		return;
	}
	cuse_server_is_closing(pcs);
	/* final client wakeup, if any */
	cuse_server_wakeup_all_client_locked(pcs);

	TAILQ_REMOVE(&cuse_server_head, pcs, entry);

	while ((pcsd = TAILQ_FIRST(&pcs->hdev)) != NULL) {
		TAILQ_REMOVE(&pcs->hdev, pcsd, entry);
		cuse_unlock();
		cuse_server_free_dev(pcsd);
		cuse_lock();
	}

	cuse_free_unit_by_id_locked(pcs, -1);

	while ((mem = TAILQ_FIRST(&pcs->hmem)) != NULL) {
		TAILQ_REMOVE(&pcs->hmem, mem, entry);
		cuse_unlock();
		cuse_vm_memory_free(mem);
		cuse_lock();
	}

	knlist_clear(&pcs->selinfo.si_note, 1);
	knlist_destroy(&pcs->selinfo.si_note);

	cuse_unlock();

	seldrain(&pcs->selinfo);

	cv_destroy(&pcs->cv);

	free(pcs, M_CUSE);
}