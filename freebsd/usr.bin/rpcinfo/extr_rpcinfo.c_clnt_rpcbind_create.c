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
struct netconfig {int dummy; } ;
struct netbuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ cf_stat; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ RPC_SUCCESS ; 
 scalar_t__ RPC_UNKNOWNPROTO ; 
 int /*<<< orphan*/  __rpc_endconf (void*) ; 
 struct netconfig* __rpc_getconf (void*) ; 
 void* __rpc_setconf (char const*) ; 
 int /*<<< orphan*/ * getclnthandle (char*,struct netconfig*,int,struct netbuf**) ; 
 TYPE_1__ rpc_createerr ; 

__attribute__((used)) static CLIENT *
clnt_rpcbind_create(char *host, int rpcbversnum, struct netbuf **targaddr)
{
	static const char *tlist[3] = {
		"circuit_n", "circuit_v", "datagram_v"
	};
	int i;
	struct netconfig *nconf;
	CLIENT *clnt = NULL;
	void *handle;

	rpc_createerr.cf_stat = RPC_SUCCESS;
	for (i = 0; i < 3; i++) {
		if ((handle = __rpc_setconf(tlist[i])) == NULL)
			continue;
		while (clnt == (CLIENT *)NULL) {
			if ((nconf = __rpc_getconf(handle)) == NULL) {
				if (rpc_createerr.cf_stat == RPC_SUCCESS)
				    rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
				break;
			}
			clnt = getclnthandle(host, nconf, rpcbversnum,
					targaddr);
		}
		if (clnt)
			break;
		__rpc_endconf(handle);
	}
	return (clnt);
}