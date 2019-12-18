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
 struct process_id PID ; 
 int TL_UDP_OBSOLETE_HASH ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  out_buf_send_error (struct process_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct raw_message*) ; 
 int rwm_create (struct raw_message*,int*,int) ; 

void send_error_obsolete_hash (struct udp_socket *u, struct udp_message *msg, long long hash) {
  static int z[10];
  z[0] = TL_UDP_OBSOLETE_HASH;
  *(long long *)(z + 1) = hash;
  *(struct process_id *)(z + 3) = PID;
  
  struct raw_message raw;
  assert (rwm_create (&raw, z, 24) == 24);

  out_buf_send_error (&PID, 0, 0, msg->ipv6, msg->port, &raw);
}