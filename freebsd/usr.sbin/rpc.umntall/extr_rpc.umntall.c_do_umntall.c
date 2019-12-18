#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  cl_auth; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNTPROC_UMNTALL ; 
 int /*<<< orphan*/  MOUNTPROG ; 
 int /*<<< orphan*/  MOUNTVERS ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  auth_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authunix_create_default () ; 
 int clnt_call (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval) ; 
 TYPE_1__* clnt_create_timed (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct timeval*) ; 
 int /*<<< orphan*/  clnt_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_void ; 

int
do_umntall(char *hostname) {
	enum clnt_stat clnt_stat;
	struct timeval try;
	CLIENT *clp;

	try.tv_sec = 3;
	try.tv_usec = 0;
	clp = clnt_create_timed(hostname, MOUNTPROG, MOUNTVERS, "udp",
	    &try);
	if (clp == NULL) {
		warnx("%s: %s", hostname, clnt_spcreateerror("MOUNTPROG"));
		return (0);
	}
	clp->cl_auth = authunix_create_default();
	clnt_stat = clnt_call(clp, MOUNTPROC_UMNTALL,
	    (xdrproc_t)xdr_void, (caddr_t)0,
	    (xdrproc_t)xdr_void, (caddr_t)0, try);
	if (clnt_stat != RPC_SUCCESS)
		warnx("%s: %s", hostname, clnt_sperror(clp, "MOUNTPROC_UMNTALL"));
	auth_destroy(clp->cl_auth);
	clnt_destroy(clp);
	return (clnt_stat == RPC_SUCCESS);
}