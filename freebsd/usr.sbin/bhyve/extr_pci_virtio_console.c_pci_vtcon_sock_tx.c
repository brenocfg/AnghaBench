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
struct pci_vtcon_sock {int vss_conn_fd; int vss_open; int /*<<< orphan*/  vss_conn_evp; } ;
struct pci_vtcon_port {int dummy; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mevent_delete_close (int /*<<< orphan*/ ) ; 
 int stream_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_vtcon_sock_tx(struct pci_vtcon_port *port, void *arg, struct iovec *iov,
    int niov)
{
	struct pci_vtcon_sock *sock;
	int i, ret;

	sock = (struct pci_vtcon_sock *)arg;

	if (sock->vss_conn_fd == -1)
		return;

	for (i = 0; i < niov; i++) {
		ret = stream_write(sock->vss_conn_fd, iov[i].iov_base,
		    iov[i].iov_len);
		if (ret <= 0)
			break;
	}

	if (ret <= 0) {
		mevent_delete_close(sock->vss_conn_evp);
		sock->vss_conn_fd = -1;
		sock->vss_open = false;
	}
}