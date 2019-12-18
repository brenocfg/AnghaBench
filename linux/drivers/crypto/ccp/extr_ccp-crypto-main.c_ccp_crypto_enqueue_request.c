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
struct crypto_async_request {int flags; int /*<<< orphan*/  tfm; } ;
struct ccp_crypto_cmd {int /*<<< orphan*/  tfm; struct crypto_async_request* req; struct ccp_cmd* cmd; } ;
struct ccp_cmd {int /*<<< orphan*/  flags; struct ccp_crypto_cmd* data; int /*<<< orphan*/  callback; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_CMD_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ccp_crypto_complete ; 
 int ccp_crypto_enqueue_cmd (struct ccp_crypto_cmd*) ; 
 struct ccp_crypto_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 

int ccp_crypto_enqueue_request(struct crypto_async_request *req,
			       struct ccp_cmd *cmd)
{
	struct ccp_crypto_cmd *crypto_cmd;
	gfp_t gfp;

	gfp = req->flags & CRYPTO_TFM_REQ_MAY_SLEEP ? GFP_KERNEL : GFP_ATOMIC;

	crypto_cmd = kzalloc(sizeof(*crypto_cmd), gfp);
	if (!crypto_cmd)
		return -ENOMEM;

	/* The tfm pointer must be saved and not referenced from the
	 * crypto_async_request (req) pointer because it is used after
	 * completion callback for the request and the req pointer
	 * might not be valid anymore.
	 */
	crypto_cmd->cmd = cmd;
	crypto_cmd->req = req;
	crypto_cmd->tfm = req->tfm;

	cmd->callback = ccp_crypto_complete;
	cmd->data = crypto_cmd;

	if (req->flags & CRYPTO_TFM_REQ_MAY_BACKLOG)
		cmd->flags |= CCP_CMD_MAY_BACKLOG;
	else
		cmd->flags &= ~CCP_CMD_MAY_BACKLOG;

	return ccp_crypto_enqueue_cmd(crypto_cmd);
}