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
struct cuse_server {int /*<<< orphan*/  hcli; } ;
struct cuse_client_command {int /*<<< orphan*/  cv; int /*<<< orphan*/  sx; } ;
struct cuse_client {struct cuse_server* server; struct cuse_client_command* cmds; } ;

/* Variables and functions */
 int CUSE_CMD_MAX ; 
 int /*<<< orphan*/  M_CUSE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cuse_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_client_is_closing (struct cuse_client*) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_server_unref (struct cuse_server*) ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct cuse_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cuse_client_free(void *arg)
{
	struct cuse_client *pcc = arg;
	struct cuse_client_command *pccmd;
	struct cuse_server *pcs;
	int n;

	cuse_lock();
	cuse_client_is_closing(pcc);
	TAILQ_REMOVE(&pcc->server->hcli, pcc, entry);
	cuse_unlock();

	for (n = 0; n != CUSE_CMD_MAX; n++) {

		pccmd = &pcc->cmds[n];

		sx_destroy(&pccmd->sx);
		cv_destroy(&pccmd->cv);
	}

	pcs = pcc->server;

	free(pcc, M_CUSE);

	/* drop reference on server */
	cuse_server_unref(pcs);
}