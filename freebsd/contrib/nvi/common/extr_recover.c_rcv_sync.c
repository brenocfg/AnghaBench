#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_23__ {scalar_t__ (* sync ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {int /*<<< orphan*/  rcv_path; int /*<<< orphan*/  rcv_mpath; TYPE_6__* db; } ;
struct TYPE_21__ {TYPE_1__* gp; TYPE_3__* ep; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* scr_busy ) (TYPE_2__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SCR ;
typedef  TYPE_3__ EXF ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY_OFF ; 
 int /*<<< orphan*/  BUSY_ON ; 
 int /*<<< orphan*/  F_CLR (TYPE_3__*,int) ; 
 scalar_t__ F_ISSET (TYPE_3__*,int) ; 
 int F_MODIFIED ; 
 int F_RCV_NORM ; 
 int F_RCV_ON ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int) ; 
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_RECDIR ; 
 char* O_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCV_EMAIL ; 
 int /*<<< orphan*/  RCV_ENDSESSION ; 
 int /*<<< orphan*/  RCV_PRESERVE ; 
 int /*<<< orphan*/  RCV_SNAPSHOT ; 
 int /*<<< orphan*/  R_RECNOSYNC ; 
 scalar_t__ close (int) ; 
 scalar_t__ file_end (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* join (char*,char*) ; 
 int /*<<< orphan*/  msgq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq_str (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ opts_empty (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rcv_copy (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_email (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rcv_mailfile (TYPE_2__*,int,char*) ; 
 int rcv_mktemp (TYPE_2__*,char*,char*) ; 
 scalar_t__ stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
rcv_sync(
	SCR *sp,
	u_int flags)
{
	EXF *ep;
	int fd, rval;
	char *dp, *buf;

	/* Make sure that there's something to recover/sync. */
	ep = sp->ep;
	if (ep == NULL || !F_ISSET(ep, F_RCV_ON))
		return (0);

	/* Sync the file if it's been modified. */
	if (F_ISSET(ep, F_MODIFIED)) {
		if (ep->db->sync(ep->db, R_RECNOSYNC)) {
			F_CLR(ep, F_RCV_ON | F_RCV_NORM);
			msgq_str(sp, M_SYSERR,
			    ep->rcv_path, "060|File backup failed: %s");
			return (1);
		}

		/* REQUEST: don't remove backing file on exit. */
		if (LF_ISSET(RCV_PRESERVE))
			F_SET(ep, F_RCV_NORM);

		/* REQUEST: send email. */
		if (LF_ISSET(RCV_EMAIL))
			rcv_email(sp, ep->rcv_mpath);
	}

	/*
	 * !!!
	 * Each time the user exec's :preserve, we have to snapshot all of
	 * the recovery information, i.e. it's like the user re-edited the
	 * file.  We copy the DB(3) backing file, and then create a new mail
	 * recovery file, it's simpler than exiting and reopening all of the
	 * underlying files.
	 *
	 * REQUEST: snapshot the file.
	 */
	rval = 0;
	if (LF_ISSET(RCV_SNAPSHOT)) {
		if (opts_empty(sp, O_RECDIR, 0))
			goto err;
		dp = O_STR(sp, O_RECDIR);
		if ((buf = join(dp, "vi.XXXXXX")) == NULL) {
			msgq(sp, M_SYSERR, NULL);
			goto err;
		}
		if ((fd = rcv_mktemp(sp, buf, dp)) == -1) {
			free(buf);
			goto err;
		}
		sp->gp->scr_busy(sp,
		    "061|Copying file for recovery...", BUSY_ON);
		if (rcv_copy(sp, fd, ep->rcv_path) ||
		    close(fd) || rcv_mailfile(sp, 1, buf)) {
			(void)unlink(buf);
			(void)close(fd);
			rval = 1;
		}
		free(buf);
		sp->gp->scr_busy(sp, NULL, BUSY_OFF);
	}
	if (0) {
err:		rval = 1;
	}

	/* REQUEST: end the file session. */
	if (LF_ISSET(RCV_ENDSESSION) && file_end(sp, NULL, 1))
		rval = 1;

	return (rval);
}