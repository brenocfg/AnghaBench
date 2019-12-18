#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct md_s {int flags; int* procp; int /*<<< orphan*/  unit; scalar_t__ uma; scalar_t__ indir; int /*<<< orphan*/ * object; int /*<<< orphan*/ * cred; TYPE_1__* vnode; int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  stat_mtx; int /*<<< orphan*/ * devstat; scalar_t__ gp; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_vflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct md_s*,int /*<<< orphan*/ ) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int MD_EXITING ; 
 int MD_PROVIDERGONE ; 
 int MD_READONLY ; 
 int MD_SHUTDOWN ; 
 int /*<<< orphan*/  M_MD ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VV_MD ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_indir (struct md_s*,scalar_t__) ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct md_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_wither_geom (scalar_t__,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  md_uh ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (scalar_t__) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_close (TYPE_1__*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  vn_lock (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wakeup (struct md_s*) ; 

__attribute__((used)) static int
mddestroy(struct md_s *sc, struct thread *td)
{

	if (sc->gp) {
		g_topology_lock();
		g_wither_geom(sc->gp, ENXIO);
		g_topology_unlock();

		mtx_lock(&sc->queue_mtx);
		while (!(sc->flags & MD_PROVIDERGONE))
			msleep(&sc->flags, &sc->queue_mtx, PRIBIO, "mddestroy", 0);
		mtx_unlock(&sc->queue_mtx);
	}
	if (sc->devstat) {
		devstat_remove_entry(sc->devstat);
		sc->devstat = NULL;
	}
	mtx_lock(&sc->queue_mtx);
	sc->flags |= MD_SHUTDOWN;
	wakeup(sc);
	while (!(sc->flags & MD_EXITING))
		msleep(sc->procp, &sc->queue_mtx, PRIBIO, "mddestroy", hz / 10);
	mtx_unlock(&sc->queue_mtx);
	mtx_destroy(&sc->stat_mtx);
	mtx_destroy(&sc->queue_mtx);
	if (sc->vnode != NULL) {
		vn_lock(sc->vnode, LK_EXCLUSIVE | LK_RETRY);
		sc->vnode->v_vflag &= ~VV_MD;
		VOP_UNLOCK(sc->vnode, 0);
		(void)vn_close(sc->vnode, sc->flags & MD_READONLY ?
		    FREAD : (FREAD|FWRITE), sc->cred, td);
	}
	if (sc->cred != NULL)
		crfree(sc->cred);
	if (sc->object != NULL)
		vm_object_deallocate(sc->object);
	if (sc->indir)
		destroy_indir(sc, sc->indir);
	if (sc->uma)
		uma_zdestroy(sc->uma);

	LIST_REMOVE(sc, list);
	free_unr(md_uh, sc->unit);
	free(sc, M_MD);
	return (0);
}