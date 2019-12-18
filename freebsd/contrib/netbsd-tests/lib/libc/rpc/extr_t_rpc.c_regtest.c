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
typedef  int /*<<< orphan*/  xdrproc_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  ERRX (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  PLUSONE ; 
 int /*<<< orphan*/  PROGNUM ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  SKIPX (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SVC_FDSET_POLL ; 
 int /*<<< orphan*/  VERSNUM ; 
 int atoi (char const*) ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clnt_create (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int clnt_spcreateerror (char*) ; 
 int clnt_sperrno (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  sleep (int) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svc_fdset_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_run () ; 
 int /*<<< orphan*/  tout ; 
 scalar_t__ xdr_int ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static int
regtest(const char *hostname, const char *transp, const char *arg, int p)
{
	CLIENT         *clnt;
	int 		num, resp;
	enum clnt_stat  rv;
	pid_t		pid;

	if (arg)
		num = atoi(arg);
	else
		num = 0;

#ifdef __NetBSD__
	svc_fdset_init(p ? SVC_FDSET_POLL : 0);
#endif
	if (!svc_create(server, PROGNUM, VERSNUM, transp))
	{
		SKIPX(EXIT_FAILURE, "Cannot create server %d", num);
	}

	switch ((pid = fork())) {
	case 0:
		DPRINTF("Calling svc_run\n");
		svc_run();
		ERRX(EXIT_FAILURE, "svc_run returned %d!", num);
	case -1:
		ERRX(EXIT_FAILURE, "Fork failed (%s)", strerror(errno));
	default:
		sleep(1);
		break;
	}

	DPRINTF("Initializing client\n");
	clnt = clnt_create(hostname, PROGNUM, VERSNUM, transp);
	if (clnt == NULL)
		ERRX(EXIT_FAILURE, "%s",
		    clnt_spcreateerror("clnt_raw_create"));
	rv = clnt_call(clnt, PLUSONE, (xdrproc_t)xdr_int, (void *)&num,
	    (xdrproc_t)xdr_int, (void *)&resp, tout);
	if (rv != RPC_SUCCESS)
		ERRX(EXIT_FAILURE, "clnt_call: %s", clnt_sperrno(rv));
	DPRINTF("Got %d\n", resp);
	if (++num != resp)
		ERRX(EXIT_FAILURE, "expected %d got %d", num, resp);
	rv = clnt_call(clnt, DESTROY, (xdrproc_t)xdr_void, NULL,
	    (xdrproc_t)xdr_void, NULL, tout);
	if (rv != RPC_SUCCESS)
		ERRX(EXIT_FAILURE, "clnt_call: %s", clnt_sperrno(rv));
	clnt_destroy(clnt);

	return EXIT_SUCCESS;
}