#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  recno_t ;
struct TYPE_19__ {scalar_t__ (* sync ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  rcv_path; TYPE_6__* db; int /*<<< orphan*/ * rcv_mpath; } ;
struct TYPE_17__ {TYPE_1__* gp; TYPE_3__* ep; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* scr_busy ) (TYPE_2__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY_OFF ; 
 int /*<<< orphan*/  BUSY_ON ; 
 int /*<<< orphan*/  F_CLR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_FIRSTMODIFY ; 
 int /*<<< orphan*/  F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_RCV_ON ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  R_RECNOSYNC ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int) ; 
 scalar_t__ db_last (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgq_str (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rcv_mailfile (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

int
rcv_init(SCR *sp)
{
	EXF *ep;
	recno_t lno;

	ep = sp->ep;

	/* Only do this once. */
	F_CLR(ep, F_FIRSTMODIFY);

	/* If we already know the file isn't recoverable, we're done. */
	if (!F_ISSET(ep, F_RCV_ON))
		return (0);

	/* Turn off recoverability until we figure out if this will work. */
	F_CLR(ep, F_RCV_ON);

	/* Test if we're recovering a file, not editing one. */
	if (ep->rcv_mpath == NULL) {
		/* Build a file to mail to the user. */
		if (rcv_mailfile(sp, 0, NULL))
			goto err;

		/* Force a read of the entire file. */
		if (db_last(sp, &lno))
			goto err;

		/* Turn on a busy message, and sync it to backing store. */
		sp->gp->scr_busy(sp,
		    "057|Copying file for recovery...", BUSY_ON);
		if (ep->db->sync(ep->db, R_RECNOSYNC)) {
			msgq_str(sp, M_SYSERR, ep->rcv_path,
			    "058|Preservation failed: %s");
			sp->gp->scr_busy(sp, NULL, BUSY_OFF);
			goto err;
		}
		sp->gp->scr_busy(sp, NULL, BUSY_OFF);
	}

	/* Turn off the owner execute bit. */
	(void)chmod(ep->rcv_path, S_IRUSR | S_IWUSR);

	/* We believe the file is recoverable. */
	F_SET(ep, F_RCV_ON);
	return (0);

err:	msgq(sp, M_ERR,
	    "059|Modifications not recoverable if the session fails");
	return (1);
}