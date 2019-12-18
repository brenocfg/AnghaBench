#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_2__ {char* name; scalar_t__ state; } ;
typedef  TYPE_1__ nlm4_notify ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int /*<<< orphan*/  NLM4_FREE_ALL ; 
 int /*<<< orphan*/  NLM_PROG ; 
 int /*<<< orphan*/  NLM_VERS4 ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  clnt_perrno (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ geteuid () ; 
 int rpc_call (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ xdr_nlm4_notify ; 
 scalar_t__ xdr_void ; 

int
main(int argc, char **argv)
{
	enum clnt_stat stat;
	char *hostname;
	nlm4_notify notify;

	if (argc != 2) {
		fprintf(stderr, "Usage: clear_locks <hostname>\n");
		exit(1);
	}
	hostname = argv[1];

	if (geteuid() != 0) {
		fprintf(stderr, "clear_locks: must be root\n");
		exit(1);
	}

	notify.name = hostname;
	notify.state = 0;
	stat = rpc_call("localhost", NLM_PROG, NLM_VERS4, NLM4_FREE_ALL,
	    (xdrproc_t) xdr_nlm4_notify, (void *) &notify,
	    (xdrproc_t) xdr_void, NULL, NULL);

	if (stat != RPC_SUCCESS) {
		clnt_perrno(stat);
		exit(1);
	}
	fprintf(stderr, "clear_locks: cleared locks for hostname %s\n",
	    hostname);

	return (0);
}