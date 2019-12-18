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
struct nfssockreq {int /*<<< orphan*/  nr_mtx; int /*<<< orphan*/ * nr_client; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_CLOSE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLNT_RELEASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_gss_secpurge_call (int /*<<< orphan*/ *) ; 

void
newnfs_disconnect(struct nfssockreq *nrp)
{
	CLIENT *client;

	mtx_lock(&nrp->nr_mtx);
	if (nrp->nr_client != NULL) {
		client = nrp->nr_client;
		nrp->nr_client = NULL;
		mtx_unlock(&nrp->nr_mtx);
		rpc_gss_secpurge_call(client);
		CLNT_CLOSE(client);
		CLNT_RELEASE(client);
	} else {
		mtx_unlock(&nrp->nr_mtx);
	}
}