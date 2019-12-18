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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  WALLPROC_WALL ; 
 int /*<<< orphan*/  WALLPROG ; 
 int /*<<< orphan*/  WALLVERS ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct timeval) ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_spcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_sperror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makemsg (char*) ; 
 int /*<<< orphan*/  mbuf ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ xdr_void ; 
 scalar_t__ xdr_wrapstring ; 

int
main(int argc, char *argv[])
{
	char *wallhost, res;
	CLIENT *cl;
	struct timeval tv;

	if ((argc < 2) || (argc > 3))
		usage();

	wallhost = argv[1];

	makemsg(argv[2]);

	/*
	 * Create client "handle" used for calling MESSAGEPROG on the
	 * server designated on the command line. We tell the rpc package
	 * to use the "tcp" protocol when contacting the server.
	*/
	cl = clnt_create(wallhost, WALLPROG, WALLVERS, "udp");
	if (cl == NULL) {
		/*
		 * Couldn't establish connection with server.
		 * Print error message and die.
		 */
		errx(1, "%s", clnt_spcreateerror(wallhost));
	}

	tv.tv_sec = 15;		/* XXX ?? */
	tv.tv_usec = 0;
	if (clnt_call(cl, WALLPROC_WALL, (xdrproc_t)xdr_wrapstring, &mbuf,
	    (xdrproc_t)xdr_void, &res, tv) != RPC_SUCCESS) {
		/*
		 * An error occurred while calling the server.
		 * Print error message and die.
		 */
		errx(1, "%s", clnt_sperror(cl, wallhost));
	}

	return (0);
}