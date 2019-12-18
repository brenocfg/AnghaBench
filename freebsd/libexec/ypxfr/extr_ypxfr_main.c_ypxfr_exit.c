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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ypxfrstat ;
typedef  scalar_t__ yppush_status ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;} ;
struct TYPE_5__ {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int RPC_ANYSOCK ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * clntudp_create (int /*<<< orphan*/ *,scalar_t__,int,struct timeval,int*) ; 
 TYPE_3__* dbp ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int unlink (char*) ; 
 int /*<<< orphan*/  yp_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yppushproc_xfrresp_1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ypxfr_callback_addr ; 
 scalar_t__ ypxfr_prognum ; 
 TYPE_1__ ypxfr_resp ; 
 int /*<<< orphan*/  ypxfrerr_string (scalar_t__) ; 

__attribute__((used)) static void
ypxfr_exit(ypxfrstat retval, char *temp)
{
	CLIENT *clnt;
	int sock = RPC_ANYSOCK;
	struct timeval timeout;

	/* Clean up no matter what happened previously. */
	if (temp != NULL) {
		if (dbp != NULL)
			(void)(dbp->close)(dbp);
		if (unlink(temp) == -1) {
			yp_error("failed to unlink %s",strerror(errno));
		}
	}

	if (ypxfr_prognum) {
		timeout.tv_sec = 20;
		timeout.tv_usec = 0;

		if ((clnt = clntudp_create(&ypxfr_callback_addr, ypxfr_prognum,
					1, timeout, &sock)) == NULL) {
			yp_error("%s", clnt_spcreateerror("failed to "
			    "establish callback handle"));
			exit(1);
		}

		ypxfr_resp.status = (yppush_status)retval;

		if (yppushproc_xfrresp_1(&ypxfr_resp, clnt) == NULL) {
			yp_error("%s", clnt_sperror(clnt, "callback failed"));
			clnt_destroy(clnt);
			exit(1);
		}
		clnt_destroy(clnt);
	} else {
		yp_error("Exiting: %s", ypxfrerr_string(retval));
	}

	exit(0);
}