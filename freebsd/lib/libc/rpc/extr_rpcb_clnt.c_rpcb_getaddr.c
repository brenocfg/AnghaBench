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
struct timeval {int dummy; } ;
struct netconfig {int dummy; } ;
struct netbuf {scalar_t__ len; scalar_t__ maxlen; struct netbuf* buf; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_2__ {int /*<<< orphan*/  cf_stat; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RPC_FAILED ; 
 int /*<<< orphan*/  TRUE ; 
 struct netbuf* __rpcb_findaddr_timed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*,char*,int /*<<< orphan*/ **,struct timeval*) ; 
 int /*<<< orphan*/  free (struct netbuf*) ; 
 int /*<<< orphan*/  memcpy (struct netbuf*,struct netbuf*,size_t) ; 
 TYPE_1__ rpc_createerr ; 

bool_t
rpcb_getaddr(rpcprog_t program, rpcvers_t version, const struct netconfig *nconf,
    struct netbuf *address, const char *host)
{
	struct netbuf *na;

	if ((na = __rpcb_findaddr_timed(program, version,
	    (struct netconfig *) nconf, (char *) host,
	    (CLIENT **) NULL, (struct timeval *) NULL)) == NULL)
		return (FALSE);

	if (na->len > address->maxlen) {
		/* Too long address */
		free(na->buf);
		free(na);
		rpc_createerr.cf_stat = RPC_FAILED;
		return (FALSE);
	}
	memcpy(address->buf, na->buf, (size_t)na->len);
	address->len = na->len;
	free(na->buf);
	free(na);
	return (TRUE);
}