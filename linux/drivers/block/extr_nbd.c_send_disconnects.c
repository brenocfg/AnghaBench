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
struct nbd_sock {int /*<<< orphan*/  tx_lock; } ;
struct nbd_request {int /*<<< orphan*/  type; int /*<<< orphan*/  magic; } ;
struct nbd_device {int /*<<< orphan*/  disk; struct nbd_config* config; } ;
struct nbd_config {int num_connections; struct nbd_sock** socks; } ;
struct kvec {int iov_len; struct nbd_request* iov_base; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  request ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_CMD_DISC ; 
 int /*<<< orphan*/  NBD_REQUEST_MAGIC ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sock_xmit (struct nbd_device*,int,int,struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_disconnects(struct nbd_device *nbd)
{
	struct nbd_config *config = nbd->config;
	struct nbd_request request = {
		.magic = htonl(NBD_REQUEST_MAGIC),
		.type = htonl(NBD_CMD_DISC),
	};
	struct kvec iov = {.iov_base = &request, .iov_len = sizeof(request)};
	struct iov_iter from;
	int i, ret;

	for (i = 0; i < config->num_connections; i++) {
		struct nbd_sock *nsock = config->socks[i];

		iov_iter_kvec(&from, WRITE, &iov, 1, sizeof(request));
		mutex_lock(&nsock->tx_lock);
		ret = sock_xmit(nbd, i, 1, &from, 0, NULL);
		if (ret <= 0)
			dev_err(disk_to_dev(nbd->disk),
				"Send disconnect failed %d\n", ret);
		mutex_unlock(&nsock->tx_lock);
	}
}