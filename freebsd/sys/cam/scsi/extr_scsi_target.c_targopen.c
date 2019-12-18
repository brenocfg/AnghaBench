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
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct targ_softc {TYPE_1__ read_select; int /*<<< orphan*/  user_ccb_queue; int /*<<< orphan*/  abort_queue; int /*<<< orphan*/  work_queue; int /*<<< orphan*/  pending_ccb_queue; int /*<<< orphan*/ * path; int /*<<< orphan*/ * periph; int /*<<< orphan*/  state; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TARG ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TARG_STATE_OPENED ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct targ_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct targ_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  targcdevdtor ; 

__attribute__((used)) static int
targopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct targ_softc *softc;

	/* Allocate its softc, initialize it */
	softc = malloc(sizeof(*softc), M_TARG,
	       M_WAITOK | M_ZERO);
	softc->state = TARG_STATE_OPENED;
	softc->periph = NULL;
	softc->path = NULL;

	TAILQ_INIT(&softc->pending_ccb_queue);
	TAILQ_INIT(&softc->work_queue);
	TAILQ_INIT(&softc->abort_queue);
	TAILQ_INIT(&softc->user_ccb_queue);
	knlist_init_mtx(&softc->read_select.si_note, NULL);

	devfs_set_cdevpriv(softc, targcdevdtor);
	return (0);
}