#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpu_cc_ent {int /*<<< orphan*/  ctx; } ;
struct drvdb_ent {int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  dro_drivername; } ;
struct TYPE_3__ {int /*<<< orphan*/  dro_drivername; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct fpu_cc_ent* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct fpu_cc_ent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (int /*<<< orphan*/ *) ; 
 struct fpu_cc_ent* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drvdb_head ; 
 int /*<<< orphan*/  drvdb_mtx ; 
 int /*<<< orphan*/  entries ; 
 TYPE_2__ fake_pccard_driver ; 
 TYPE_1__ fake_pci_driver ; 
 int /*<<< orphan*/  fpu_busy_head ; 
 int /*<<< orphan*/  fpu_busy_mtx ; 
 int /*<<< orphan*/  fpu_free_head ; 
 int /*<<< orphan*/  fpu_free_mtx ; 
 int /*<<< orphan*/  fpu_kern_free_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fpu_cc_ent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  my_tids ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_oldldt ; 

int
windrv_libfini(void)
{
	struct drvdb_ent	*d;
#ifdef __amd64__
	struct fpu_cc_ent	*ent;
#endif

	mtx_lock(&drvdb_mtx); 
	while(STAILQ_FIRST(&drvdb_head) != NULL) {
		d = STAILQ_FIRST(&drvdb_head);
		STAILQ_REMOVE_HEAD(&drvdb_head, link);
		free(d, M_DEVBUF);
	}
	mtx_unlock(&drvdb_mtx);

	RtlFreeUnicodeString(&fake_pci_driver.dro_drivername);
	RtlFreeUnicodeString(&fake_pccard_driver.dro_drivername);

	mtx_destroy(&drvdb_mtx);

#ifdef __i386__
	smp_rendezvous(NULL, x86_oldldt, NULL, NULL);
	ExFreePool(my_tids);
#endif
#ifdef __amd64__
	while ((ent = LIST_FIRST(&fpu_free_head)) != NULL) {
		LIST_REMOVE(ent, entries);
		fpu_kern_free_ctx(ent->ctx);
		free(ent, M_DEVBUF);
	}
	mtx_destroy(&fpu_free_mtx);

	ent = LIST_FIRST(&fpu_busy_head);
	KASSERT(ent == NULL, ("busy fpu context list is not empty"));
	mtx_destroy(&fpu_busy_mtx);
#endif
	return (0);
}