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
struct udp_socket {int dummy; } ;
struct udp_message {int dummy; } ;
struct process_id {int dummy; } ;

/* Variables and functions */

void send_error_wrong_pid (struct udp_socket *u, struct udp_message *msg, struct process_id *remote_pid, struct process_id *pid) {
}