#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* sk; } ;
struct recv_thread_args {int index; int /*<<< orphan*/  work; struct nbd_device* nbd; } ;
struct nbd_sock {int dead; int fallback_index; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  cookie; struct socket* sock; } ;
struct TYPE_3__ {scalar_t__ timeout; } ;
struct nbd_device {int /*<<< orphan*/  recv_workq; int /*<<< orphan*/  config_refs; TYPE_1__ tag_set; struct nbd_config* config; } ;
struct nbd_config {int num_connections; int /*<<< orphan*/  conn_wait; int /*<<< orphan*/  live_connections; int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  recv_threads; struct nbd_sock** socks; } ;
struct TYPE_4__ {scalar_t__ sk_sndtimeo; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBD_RT_DISCONNECTED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct recv_thread_args*) ; 
 struct recv_thread_args* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct socket* nbd_get_socket (struct nbd_device*,unsigned long,int*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_work ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_set_memalloc (TYPE_2__*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nbd_reconnect_socket(struct nbd_device *nbd, unsigned long arg)
{
	struct nbd_config *config = nbd->config;
	struct socket *sock, *old;
	struct recv_thread_args *args;
	int i;
	int err;

	sock = nbd_get_socket(nbd, arg, &err);
	if (!sock)
		return err;

	args = kzalloc(sizeof(*args), GFP_KERNEL);
	if (!args) {
		sockfd_put(sock);
		return -ENOMEM;
	}

	for (i = 0; i < config->num_connections; i++) {
		struct nbd_sock *nsock = config->socks[i];

		if (!nsock->dead)
			continue;

		mutex_lock(&nsock->tx_lock);
		if (!nsock->dead) {
			mutex_unlock(&nsock->tx_lock);
			continue;
		}
		sk_set_memalloc(sock->sk);
		if (nbd->tag_set.timeout)
			sock->sk->sk_sndtimeo = nbd->tag_set.timeout;
		atomic_inc(&config->recv_threads);
		refcount_inc(&nbd->config_refs);
		old = nsock->sock;
		nsock->fallback_index = -1;
		nsock->sock = sock;
		nsock->dead = false;
		INIT_WORK(&args->work, recv_work);
		args->index = i;
		args->nbd = nbd;
		nsock->cookie++;
		mutex_unlock(&nsock->tx_lock);
		sockfd_put(old);

		clear_bit(NBD_RT_DISCONNECTED, &config->runtime_flags);

		/* We take the tx_mutex in an error path in the recv_work, so we
		 * need to queue_work outside of the tx_mutex.
		 */
		queue_work(nbd->recv_workq, &args->work);

		atomic_inc(&config->live_connections);
		wake_up(&config->conn_wait);
		return 0;
	}
	sockfd_put(sock);
	kfree(args);
	return -ENOSPC;
}