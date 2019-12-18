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
 int /*<<< orphan*/  mac_socket_label_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_socketpeer_label_free (int /*<<< orphan*/ *) ; 

void
mac_socket_destroy(struct socket *so)
{

	if (so->so_label != NULL) {
		mac_socket_label_free(so->so_label);
		so->so_label = NULL;
		mac_socketpeer_label_free(so->so_peerlabel);
		so->so_peerlabel = NULL;
	}
}