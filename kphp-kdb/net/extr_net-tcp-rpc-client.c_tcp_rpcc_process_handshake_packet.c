#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ip; } ;
struct TYPE_7__ {scalar_t__ ip; } ;
struct tcp_rpc_handshake_packet {TYPE_1__ peer_pid; TYPE_2__ sender_pid; } ;
struct tcp_rpc_data {int packet_num; scalar_t__ packet_type; int packet_len; TYPE_1__ remote_pid; } ;
struct raw_message {int dummy; } ;
struct process_id {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 TYPE_2__ PID ; 
 scalar_t__ RPC_HANDSHAKE ; 
 struct tcp_rpc_data* TCP_RPC_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  matches_pid (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 
 int rwm_fetch_data (struct raw_message*,struct tcp_rpc_handshake_packet*,int) ; 
 int /*<<< orphan*/  tcp_rpcc_send_handshake_error_packet (struct connection*,int) ; 

__attribute__((used)) static int tcp_rpcc_process_handshake_packet (struct connection *c, struct raw_message *msg) {
  struct tcp_rpc_data *D = TCP_RPC_DATA(c);
  static struct tcp_rpc_handshake_packet P;
  if (D->packet_num != -1 || D->packet_type != RPC_HANDSHAKE) {
    return -2;
  }
  if (D->packet_len != sizeof (struct tcp_rpc_handshake_packet)) {
    tcp_rpcc_send_handshake_error_packet (c, -3);
    return -3;
  }
  assert (rwm_fetch_data (msg, &P, D->packet_len) == D->packet_len);  
  if (!matches_pid (&P.sender_pid, &D->remote_pid)) {
    tcp_rpcc_send_handshake_error_packet (c, -6);
    return -6;
  }
  if (!P.sender_pid.ip) {
    P.sender_pid.ip = D->remote_pid.ip;
  }
  memcpy (&D->remote_pid, &P.sender_pid, sizeof (struct process_id));
  if (!matches_pid (&PID, &P.peer_pid)) {
    tcp_rpcc_send_handshake_error_packet (c, -4);
    return -4;
  }
  return 0;
}