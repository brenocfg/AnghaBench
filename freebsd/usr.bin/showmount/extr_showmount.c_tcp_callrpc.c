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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {scalar_t__ cf_stat; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,struct timeval) ; 
 int /*<<< orphan*/ * clnt_create (char const*,int,int,char*) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__ rpc_createerr ; 

int 
tcp_callrpc(const char *host, int prognum, int versnum, int procnum,
    xdrproc_t inproc, char *in, xdrproc_t outproc, char *out)
{
	CLIENT *client;
	struct timeval timeout;
	int rval;

	if ((client = clnt_create(host, prognum, versnum, "tcp")) == NULL &&
	    (client = clnt_create(host, prognum, versnum, "udp")) == NULL)
		return ((int) rpc_createerr.cf_stat);

	timeout.tv_sec = 25;
	timeout.tv_usec = 0;
	rval = (int) clnt_call(client, procnum, 
			       inproc, in,
			       outproc, out,
			       timeout);
	clnt_destroy(client);
 	return rval;
}