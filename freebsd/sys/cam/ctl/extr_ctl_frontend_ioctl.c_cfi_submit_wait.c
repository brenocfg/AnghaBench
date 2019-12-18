#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* be_move_done ) (union ctl_io*) ;} ;
struct TYPE_5__ {TYPE_1__* ctl_private; } ;
union ctl_io {TYPE_3__ scsiio; TYPE_2__ io_hdr; } ;
struct ctl_fe_ioctl_params {int state; int /*<<< orphan*/  sem; int /*<<< orphan*/  ioctl_mtx; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int ctl_fe_ioctl_state ;
struct TYPE_4__ {struct ctl_fe_ioctl_params* ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
#define  CTL_IOCTL_DATAMOVE 130 
#define  CTL_IOCTL_DONE 129 
#define  CTL_IOCTL_INPROG 128 
 size_t CTL_PRIV_FRONTEND ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  bzero (struct ctl_fe_ioctl_params*,int) ; 
 int /*<<< orphan*/  ctl_ioctl_do_datamove (TYPE_3__*) ; 
 int ctl_queue (union ctl_io*) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (union ctl_io*) ; 

__attribute__((used)) static int
cfi_submit_wait(union ctl_io *io)
{
	struct ctl_fe_ioctl_params params;
	ctl_fe_ioctl_state last_state;
	int done, retval;

	bzero(&params, sizeof(params));
	mtx_init(&params.ioctl_mtx, "ctliocmtx", NULL, MTX_DEF);
	cv_init(&params.sem, "ctlioccv");
	params.state = CTL_IOCTL_INPROG;
	last_state = params.state;

	io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = &params;

	CTL_DEBUG_PRINT(("cfi_submit_wait\n"));

	/* This shouldn't happen */
	if ((retval = ctl_queue(io)) != CTL_RETVAL_COMPLETE)
		return (retval);

	done = 0;

	do {
		mtx_lock(&params.ioctl_mtx);
		/*
		 * Check the state here, and don't sleep if the state has
		 * already changed (i.e. wakeup has already occurred, but we
		 * weren't waiting yet).
		 */
		if (params.state == last_state) {
			/* XXX KDM cv_wait_sig instead? */
			cv_wait(&params.sem, &params.ioctl_mtx);
		}
		last_state = params.state;

		switch (params.state) {
		case CTL_IOCTL_INPROG:
			/* Why did we wake up? */
			/* XXX KDM error here? */
			mtx_unlock(&params.ioctl_mtx);
			break;
		case CTL_IOCTL_DATAMOVE:
			CTL_DEBUG_PRINT(("got CTL_IOCTL_DATAMOVE\n"));

			/*
			 * change last_state back to INPROG to avoid
			 * deadlock on subsequent data moves.
			 */
			params.state = last_state = CTL_IOCTL_INPROG;

			mtx_unlock(&params.ioctl_mtx);
			ctl_ioctl_do_datamove(&io->scsiio);
			/*
			 * Note that in some cases, most notably writes,
			 * this will queue the I/O and call us back later.
			 * In other cases, generally reads, this routine
			 * will immediately call back and wake us up,
			 * probably using our own context.
			 */
			io->scsiio.be_move_done(io);
			break;
		case CTL_IOCTL_DONE:
			mtx_unlock(&params.ioctl_mtx);
			CTL_DEBUG_PRINT(("got CTL_IOCTL_DONE\n"));
			done = 1;
			break;
		default:
			mtx_unlock(&params.ioctl_mtx);
			/* XXX KDM error here? */
			break;
		}
	} while (done == 0);

	mtx_destroy(&params.ioctl_mtx);
	cv_destroy(&params.sem);

	return (CTL_RETVAL_COMPLETE);
}