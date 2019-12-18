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
struct beri_vtblk_softc {int /*<<< orphan*/ * cred; TYPE_1__* vnode; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_vflag; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VV_MD ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int vn_close (TYPE_1__*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  vn_lock (TYPE_1__*,int) ; 

__attribute__((used)) static int
close_file(struct beri_vtblk_softc *sc, struct thread *td)
{
	int error;

	if (sc->vnode != NULL) {
		vn_lock(sc->vnode, LK_EXCLUSIVE | LK_RETRY);
		sc->vnode->v_vflag &= ~VV_MD;
		VOP_UNLOCK(sc->vnode, 0);
		error = vn_close(sc->vnode, (FREAD|FWRITE),
				sc->cred, td);
		if (error != 0)
			return (error);
		sc->vnode = NULL;
	}

	if (sc->cred != NULL)
		crfree(sc->cred);

	return (0);
}