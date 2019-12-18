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
typedef  scalar_t__ u_long ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_in {int dummy; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ MIN_VERS ; 
 int /*<<< orphan*/  clnt_pcreateerror (char*) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,scalar_t__,scalar_t__,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,scalar_t__,scalar_t__,struct timeval,int*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static CLIENT *
clnt_com_create(struct sockaddr_in *addr, u_long prog, u_long vers,
    int *fdp, const char *trans)
{
	CLIENT *clnt;

	if (strcmp(trans, "tcp") == 0) {
		clnt = clnttcp_create(addr, prog, vers, fdp, 0, 0);
	} else {
		struct timeval to;

		to.tv_sec = 5;
		to.tv_usec = 0;
		clnt = clntudp_create(addr, prog, vers, to, fdp);
	}
	if (clnt == (CLIENT *)NULL) {
		clnt_pcreateerror("rpcinfo");
		if (vers == MIN_VERS)
			printf("program %lu is not available\n", prog);
		else
			printf("program %lu version %lu is not available\n",
							prog, vers);
		exit(1);
	}
	return (clnt);
}