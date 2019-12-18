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
struct nbd_sock {int dead; scalar_t__ sent; int /*<<< orphan*/ * pending; int /*<<< orphan*/  sock; } ;
struct nbd_device {TYPE_1__* config; int /*<<< orphan*/  index; } ;
struct link_dead_args {int /*<<< orphan*/  work; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; int /*<<< orphan*/  live_connections; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBD_RT_DISCONNECTED ; 
 int /*<<< orphan*/  NBD_RT_DISCONNECT_REQUESTED ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct link_dead_args* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbd_dead_link_work ; 
 int /*<<< orphan*/  nbd_disconnected (TYPE_1__*) ; 
 int /*<<< orphan*/  nbd_to_dev (struct nbd_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_wq ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nbd_mark_nsock_dead(struct nbd_device *nbd, struct nbd_sock *nsock,
				int notify)
{
	if (!nsock->dead && notify && !nbd_disconnected(nbd->config)) {
		struct link_dead_args *args;
		args = kmalloc(sizeof(struct link_dead_args), GFP_NOIO);
		if (args) {
			INIT_WORK(&args->work, nbd_dead_link_work);
			args->index = nbd->index;
			queue_work(system_wq, &args->work);
		}
	}
	if (!nsock->dead) {
		kernel_sock_shutdown(nsock->sock, SHUT_RDWR);
		if (atomic_dec_return(&nbd->config->live_connections) == 0) {
			if (test_and_clear_bit(NBD_RT_DISCONNECT_REQUESTED,
					       &nbd->config->runtime_flags)) {
				set_bit(NBD_RT_DISCONNECTED,
					&nbd->config->runtime_flags);
				dev_info(nbd_to_dev(nbd),
					"Disconnected due to user request.\n");
			}
		}
	}
	nsock->dead = true;
	nsock->pending = NULL;
	nsock->sent = 0;
}