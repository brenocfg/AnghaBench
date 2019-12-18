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
struct l2_packet_data {scalar_t__ pcap; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_unregister_read_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct l2_packet_data*) ; 
 int /*<<< orphan*/  pcap_close (scalar_t__) ; 
 int /*<<< orphan*/  pcap_get_selectable_fd (scalar_t__) ; 

void l2_packet_deinit(struct l2_packet_data *l2)
{
	if (l2 != NULL) {
		if (l2->pcap) {
			eloop_unregister_read_sock(
				pcap_get_selectable_fd(l2->pcap));
			pcap_close(l2->pcap);
		}
		os_free(l2);
	}
}