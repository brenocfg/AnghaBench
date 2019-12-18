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
struct l2_packet_data {scalar_t__ fd; struct l2_packet_data* own_socket_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIVSEP_CMD_L2_UNREGISTER ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct l2_packet_data*) ; 
 int /*<<< orphan*/  unlink (struct l2_packet_data*) ; 
 int /*<<< orphan*/  wpa_priv_cmd (struct l2_packet_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void l2_packet_deinit(struct l2_packet_data *l2)
{
	if (l2 == NULL)
		return;

	if (l2->fd >= 0) {
		wpa_priv_cmd(l2, PRIVSEP_CMD_L2_UNREGISTER, NULL, 0);
		eloop_unregister_read_sock(l2->fd);
		close(l2->fd);
	}

	if (l2->own_socket_path) {
		unlink(l2->own_socket_path);
		os_free(l2->own_socket_path);
	}

	os_free(l2);
}