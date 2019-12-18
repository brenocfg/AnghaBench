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
struct l2_packet_data {scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  os_free (struct l2_packet_data*) ; 

void l2_packet_deinit(struct l2_packet_data *l2)
{
	if (l2 == NULL)
		return;

	if (l2->fd >= 0) {
		eloop_unregister_read_sock(l2->fd);
		/* TODO: close connection */
	}
		
	os_free(l2);
}