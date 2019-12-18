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
struct cfiscsi_softc {int /*<<< orphan*/  targets; int /*<<< orphan*/  sessions; int /*<<< orphan*/  accept_cv; int /*<<< orphan*/  sessions_cv; int /*<<< orphan*/  lock; } ;
struct cfiscsi_data_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  bzero (struct cfiscsi_softc*,int) ; 
 int /*<<< orphan*/  cfiscsi_data_wait_zone ; 
 struct cfiscsi_softc cfiscsi_softc ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfiscsi_init(void)
{
	struct cfiscsi_softc *softc;

	softc = &cfiscsi_softc;
	bzero(softc, sizeof(*softc));
	mtx_init(&softc->lock, "cfiscsi", NULL, MTX_DEF);

	cv_init(&softc->sessions_cv, "cfiscsi_sessions");
#ifdef ICL_KERNEL_PROXY
	cv_init(&softc->accept_cv, "cfiscsi_accept");
#endif
	TAILQ_INIT(&softc->sessions);
	TAILQ_INIT(&softc->targets);

	cfiscsi_data_wait_zone = uma_zcreate("cfiscsi_data_wait",
	    sizeof(struct cfiscsi_data_wait), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);

	return (0);
}