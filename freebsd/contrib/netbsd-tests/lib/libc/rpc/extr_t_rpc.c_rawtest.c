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
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  SVCXPRT ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  ERRX (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  PLUSONE ; 
 int /*<<< orphan*/  PROGNUM ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  VERSNUM ; 
 int atoi (char const*) ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clnt_raw_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperrno (int) ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  svc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svc_raw_create () ; 
 int /*<<< orphan*/  svc_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tout ; 
 scalar_t__ xdr_int ; 

__attribute__((used)) static int
rawtest(const char *arg)
{
	CLIENT         *clnt;
	SVCXPRT        *svc;
	int 		num, resp;
	enum clnt_stat  rv;

	if (arg)
		num = atoi(arg);
	else
		num = 0;

	svc = svc_raw_create();
	if (svc == NULL)
		ERRX(EXIT_FAILURE, "Cannot create server %d", num);
	if (!svc_reg(svc, PROGNUM, VERSNUM, server, NULL))
		ERRX(EXIT_FAILURE, "Cannot register server %d", num);

	clnt = clnt_raw_create(PROGNUM, VERSNUM);
	if (clnt == NULL)
		ERRX(EXIT_FAILURE, "%s",
		    clnt_spcreateerror("clnt_raw_create"));
	rv = clnt_call(clnt, PLUSONE, (xdrproc_t)xdr_int, (void *)&num,
	    (xdrproc_t)xdr_int, (void *)&resp, tout);
	if (rv != RPC_SUCCESS)
		ERRX(EXIT_FAILURE, "clnt_call: %s", clnt_sperrno(rv));
	DPRINTF("Got %d\n", resp);
	clnt_destroy(clnt);
	svc_destroy(svc);
	if (++num != resp)
		ERRX(EXIT_FAILURE, "expected %d got %d", num, resp);

	return EXIT_SUCCESS;
}