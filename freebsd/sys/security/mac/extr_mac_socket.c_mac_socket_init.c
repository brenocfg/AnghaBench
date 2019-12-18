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
struct socket {int /*<<< orphan*/ * so_peerlabel; int /*<<< orphan*/ * so_label; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MPC_OBJECT_SOCKET ; 
 int mac_labeled ; 
 int /*<<< orphan*/ * mac_socket_label_alloc (int) ; 
 int /*<<< orphan*/  mac_socket_label_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mac_socketpeer_label_alloc (int) ; 

int
mac_socket_init(struct socket *so, int flag)
{

	if (mac_labeled & MPC_OBJECT_SOCKET) {
		so->so_label = mac_socket_label_alloc(flag);
		if (so->so_label == NULL)
			return (ENOMEM);
		so->so_peerlabel = mac_socketpeer_label_alloc(flag);
		if (so->so_peerlabel == NULL) {
			mac_socket_label_free(so->so_label);
			so->so_label = NULL;
			return (ENOMEM);
		}
	} else {
		so->so_label = NULL;
		so->so_peerlabel = NULL;
	}
	return (0);
}