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
struct socket {int dummy; } ;
struct nbd_sock {int fallback_index; int dead; scalar_t__ cookie; scalar_t__ sent; int /*<<< orphan*/ * pending; struct socket* sock; int /*<<< orphan*/  tx_lock; } ;
struct nbd_device {scalar_t__ task_setup; int /*<<< orphan*/  disk; struct nbd_config* config; } ;
struct nbd_config {int num_connections; int /*<<< orphan*/  live_connections; struct nbd_sock** socks; int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NBD_RT_BOUND ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 struct nbd_sock** krealloc (struct nbd_sock**,int,int /*<<< orphan*/ ) ; 
 struct nbd_sock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct socket* nbd_get_socket (struct nbd_device*,unsigned long,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nbd_add_socket(struct nbd_device *nbd, unsigned long arg,
			  bool netlink)
{
	struct nbd_config *config = nbd->config;
	struct socket *sock;
	struct nbd_sock **socks;
	struct nbd_sock *nsock;
	int err;

	sock = nbd_get_socket(nbd, arg, &err);
	if (!sock)
		return err;

	if (!netlink && !nbd->task_setup &&
	    !test_bit(NBD_RT_BOUND, &config->runtime_flags))
		nbd->task_setup = current;

	if (!netlink &&
	    (nbd->task_setup != current ||
	     test_bit(NBD_RT_BOUND, &config->runtime_flags))) {
		dev_err(disk_to_dev(nbd->disk),
			"Device being setup by another task");
		sockfd_put(sock);
		return -EBUSY;
	}

	socks = krealloc(config->socks, (config->num_connections + 1) *
			 sizeof(struct nbd_sock *), GFP_KERNEL);
	if (!socks) {
		sockfd_put(sock);
		return -ENOMEM;
	}
	nsock = kzalloc(sizeof(struct nbd_sock), GFP_KERNEL);
	if (!nsock) {
		sockfd_put(sock);
		return -ENOMEM;
	}

	config->socks = socks;

	nsock->fallback_index = -1;
	nsock->dead = false;
	mutex_init(&nsock->tx_lock);
	nsock->sock = sock;
	nsock->pending = NULL;
	nsock->sent = 0;
	nsock->cookie = 0;
	socks[config->num_connections++] = nsock;
	atomic_inc(&config->live_connections);

	return 0;
}