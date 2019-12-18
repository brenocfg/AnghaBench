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
typedef  int /*<<< orphan*/  ypxfrstat ;
struct TYPE_3__ {unsigned int transid; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ yppushresp_xfr ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct rpc_err {scalar_t__ re_status; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSET_TIMEOUT ; 
 scalar_t__ FALSE ; 
 int RPC_ANYSOCK ; 
 scalar_t__ RPC_SUCCESS ; 
 scalar_t__ RPC_TIMEDOUT ; 
 scalar_t__ clnt_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clnt_geterr (int /*<<< orphan*/ *,struct rpc_err*) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,unsigned int,int,struct timeval,int*) ; 
 int /*<<< orphan*/  htons (unsigned long) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 int /*<<< orphan*/ * yppushproc_xfrresp_1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ypxfr_callback(ypxfrstat rval, struct sockaddr_in *addr, unsigned int transid,
    unsigned int prognum, unsigned long port)
{
	CLIENT *clnt;
	int sock = RPC_ANYSOCK;
	struct timeval timeout;
	yppushresp_xfr ypxfr_resp;
	struct rpc_err err;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	addr->sin_port = htons(port);

	if ((clnt = clntudp_create(addr,prognum,1,timeout,&sock)) == NULL) {
		yp_error("%s: %s", inet_ntoa(addr->sin_addr),
		  clnt_spcreateerror("failed to establish callback handle"));
		return;
	}

	ypxfr_resp.status = rval;
	ypxfr_resp.transid = transid;

	/* Turn the timeout off -- we don't want to block. */
	timeout.tv_sec = 0;
	if (clnt_control(clnt, CLSET_TIMEOUT, &timeout) == FALSE)
		yp_error("failed to set timeout on ypproc_xfr callback");

	if (yppushproc_xfrresp_1(&ypxfr_resp, clnt) == NULL) {
		clnt_geterr(clnt, &err);
		if (err.re_status != RPC_SUCCESS &&
		    err.re_status != RPC_TIMEDOUT)
			yp_error("%s", clnt_sperror(clnt,
				"ypxfr callback failed"));
	}

	clnt_destroy(clnt);
	return;
}