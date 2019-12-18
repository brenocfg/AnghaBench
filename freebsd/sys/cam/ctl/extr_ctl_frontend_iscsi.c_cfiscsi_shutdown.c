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
struct cfiscsi_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  sessions_cv; int /*<<< orphan*/  accept_cv; int /*<<< orphan*/  targets; int /*<<< orphan*/  sessions; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfiscsi_data_wait_zone ; 
 struct cfiscsi_softc cfiscsi_softc ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfiscsi_shutdown(void)
{
	struct cfiscsi_softc *softc = &cfiscsi_softc;

	if (!TAILQ_EMPTY(&softc->sessions) || !TAILQ_EMPTY(&softc->targets))
		return (EBUSY);

	uma_zdestroy(cfiscsi_data_wait_zone);
#ifdef ICL_KERNEL_PROXY
	cv_destroy(&softc->accept_cv);
#endif
	cv_destroy(&softc->sessions_cv);
	mtx_destroy(&softc->lock);
	return (0);
}