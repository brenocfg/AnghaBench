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
struct cfiscsi_target {int ct_online; struct cfiscsi_softc* ct_softc; } ;
struct cfiscsi_softc {int /*<<< orphan*/ * listener; int /*<<< orphan*/  lock; int /*<<< orphan*/  online; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfiscsi_accept ; 
 int /*<<< orphan*/  icl_listen_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * icl_listen_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfiscsi_online(void *arg)
{
	struct cfiscsi_softc *softc;
	struct cfiscsi_target *ct;
	int online;

	ct = (struct cfiscsi_target *)arg;
	softc = ct->ct_softc;

	mtx_lock(&softc->lock);
	if (ct->ct_online) {
		mtx_unlock(&softc->lock);
		return;
	}
	ct->ct_online = 1;
	online = softc->online++;
	mtx_unlock(&softc->lock);
	if (online > 0)
		return;

#ifdef ICL_KERNEL_PROXY
	if (softc->listener != NULL)
		icl_listen_free(softc->listener);
	softc->listener = icl_listen_new(cfiscsi_accept);
#endif
}