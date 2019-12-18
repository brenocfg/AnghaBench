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
struct sockaddr_in {scalar_t__ sin_port; } ;
struct pmaplist {int dummy; } ;
typedef  int /*<<< orphan*/  rpcproc_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ CLNT_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pmaplist**,struct timeval) ; 
 int /*<<< orphan*/  CLNT_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PMAPPORT ; 
 scalar_t__ PMAPPROC_DUMP ; 
 int /*<<< orphan*/  PMAPPROG ; 
 int /*<<< orphan*/  PMAPVERS ; 
 scalar_t__ RPC_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_perror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_pmaplist ; 
 scalar_t__ xdr_void ; 

struct pmaplist *
pmap_getmaps(struct sockaddr_in *address)
{
	struct pmaplist *head = NULL;
	int sock = -1;
	struct timeval minutetimeout;
	CLIENT *client;

	assert(address != NULL);

	minutetimeout.tv_sec = 60;
	minutetimeout.tv_usec = 0;
	address->sin_port = htons(PMAPPORT);
	client = clnttcp_create(address, PMAPPROG,
	    PMAPVERS, &sock, 50, 500);
	if (client != NULL) {
		if (CLNT_CALL(client, (rpcproc_t)PMAPPROC_DUMP,
		    (xdrproc_t)xdr_void, NULL,
		    (xdrproc_t)xdr_pmaplist, &head, minutetimeout) !=
		    RPC_SUCCESS) {
			clnt_perror(client, "pmap_getmaps rpc problem");
		}
		CLNT_DESTROY(client);
	}
	address->sin_port = 0;
	return (head);
}