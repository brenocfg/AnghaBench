#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rp_port {int /*<<< orphan*/  rp_tty; } ;
struct TYPE_3__ {int num_ports; scalar_t__ free; int /*<<< orphan*/  hwmtx; scalar_t__ hwmtx_init; struct rp_port* rp; } ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  atomic_add_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  free (struct rp_port*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  tty_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_rel_gone (int /*<<< orphan*/ ) ; 

void
rp_releaseresource(CONTROLLER_t *ctlp)
{
	struct	rp_port *rp;
	int i;

	if (ctlp->rp != NULL) {
		for (i = 0; i < ctlp->num_ports; i++) {
			rp = ctlp->rp + i;
			atomic_add_32(&ctlp->free, 1);
			tty_lock(rp->rp_tty);
			tty_rel_gone(rp->rp_tty);
		}
                free(ctlp->rp, M_DEVBUF);
                ctlp->rp = NULL;
	}

	while (ctlp->free != 0) {
		pause("rpwt", hz / 10);
	}

	if (ctlp->hwmtx_init)
		mtx_destroy(&ctlp->hwmtx);
}