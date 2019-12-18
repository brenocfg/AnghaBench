#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  actv; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* vhba ; 
 int vhba_attach (TYPE_1__*) ; 
 int /*<<< orphan*/  vhba_detach (TYPE_1__*) ; 

int
vhba_modprobe(module_t mod, int cmd, void *arg)
{
	int error = 0;

	switch (cmd) {
	case MOD_LOAD:
		vhba = malloc(sizeof (*vhba), M_DEVBUF, M_WAITOK|M_ZERO);
		mtx_init(&vhba->lock, "vhba", NULL, MTX_DEF);
		error = vhba_attach(vhba);
		if (error) {
			mtx_destroy(&vhba->lock);
			free(vhba, M_DEVBUF);
		}
		break;
	case MOD_UNLOAD:
        	mtx_lock(&vhba->lock);
		if (TAILQ_FIRST(&vhba->done) || TAILQ_FIRST(&vhba->actv)) {
			error = EBUSY;
			mtx_unlock(&vhba->lock);
			break;
		}
		vhba_detach(vhba);
		mtx_unlock(&vhba->lock);
		mtx_destroy(&vhba->lock);
		free(vhba, M_DEVBUF);
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}