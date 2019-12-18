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
struct request {int dummy; } ;
struct nbd_sock {int /*<<< orphan*/  tx_lock; struct request* pending; scalar_t__ dead; } ;
struct nbd_device {int /*<<< orphan*/  disk; struct nbd_config* config; int /*<<< orphan*/  config_refs; } ;
struct nbd_config {int num_connections; struct nbd_sock** socks; } ;
struct nbd_cmd {int /*<<< orphan*/  status; struct nbd_device* nbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 struct request* blk_mq_rq_from_pdu (struct nbd_cmd*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 int find_fallback (struct nbd_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nbd_config_put (struct nbd_device*) ; 
 int /*<<< orphan*/  nbd_mark_nsock_dead (struct nbd_device*,struct nbd_sock*,int) ; 
 int /*<<< orphan*/  nbd_requeue_cmd (struct nbd_cmd*) ; 
 int nbd_send_cmd (struct nbd_device*,struct nbd_cmd*,int) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_shutdown (struct nbd_device*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wait_for_reconnect (struct nbd_device*) ; 

__attribute__((used)) static int nbd_handle_cmd(struct nbd_cmd *cmd, int index)
{
	struct request *req = blk_mq_rq_from_pdu(cmd);
	struct nbd_device *nbd = cmd->nbd;
	struct nbd_config *config;
	struct nbd_sock *nsock;
	int ret;

	if (!refcount_inc_not_zero(&nbd->config_refs)) {
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Socks array is empty\n");
		blk_mq_start_request(req);
		return -EINVAL;
	}
	config = nbd->config;

	if (index >= config->num_connections) {
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Attempted send on invalid socket\n");
		nbd_config_put(nbd);
		blk_mq_start_request(req);
		return -EINVAL;
	}
	cmd->status = BLK_STS_OK;
again:
	nsock = config->socks[index];
	mutex_lock(&nsock->tx_lock);
	if (nsock->dead) {
		int old_index = index;
		index = find_fallback(nbd, index);
		mutex_unlock(&nsock->tx_lock);
		if (index < 0) {
			if (wait_for_reconnect(nbd)) {
				index = old_index;
				goto again;
			}
			/* All the sockets should already be down at this point,
			 * we just want to make sure that DISCONNECTED is set so
			 * any requests that come in that were queue'ed waiting
			 * for the reconnect timer don't trigger the timer again
			 * and instead just error out.
			 */
			sock_shutdown(nbd);
			nbd_config_put(nbd);
			blk_mq_start_request(req);
			return -EIO;
		}
		goto again;
	}

	/* Handle the case that we have a pending request that was partially
	 * transmitted that _has_ to be serviced first.  We need to call requeue
	 * here so that it gets put _after_ the request that is already on the
	 * dispatch list.
	 */
	blk_mq_start_request(req);
	if (unlikely(nsock->pending && nsock->pending != req)) {
		nbd_requeue_cmd(cmd);
		ret = 0;
		goto out;
	}
	/*
	 * Some failures are related to the link going down, so anything that
	 * returns EAGAIN can be retried on a different socket.
	 */
	ret = nbd_send_cmd(nbd, cmd, index);
	if (ret == -EAGAIN) {
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Request send failed, requeueing\n");
		nbd_mark_nsock_dead(nbd, nsock, 1);
		nbd_requeue_cmd(cmd);
		ret = 0;
	}
out:
	mutex_unlock(&nsock->tx_lock);
	nbd_config_put(nbd);
	return ret;
}