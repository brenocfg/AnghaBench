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
struct udp_message {int /*<<< orphan*/  port; int /*<<< orphan*/  ipv6; } ;
struct raw_message {int dummy; } ;
struct process_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PID ; 
 int TL_UDP_DISABLE_ENCRYPTION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  out_buf_send_error (int /*<<< orphan*/ *,struct process_id*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct raw_message*) ; 
 int rwm_create (struct raw_message*,int*,int) ; 

void send_error_unsupported_encr (struct udp_socket *u, struct udp_message *msg, struct process_id *remote_pid, int generation, struct process_id *local_pid) {
  static int z[10];
  z[0] = TL_UDP_DISABLE_ENCRYPTION;
  
  struct raw_message raw;
  assert (rwm_create (&raw, z, 20) == 20);

  out_buf_send_error (&PID, remote_pid, generation, msg->ipv6, msg->port, &raw);
}