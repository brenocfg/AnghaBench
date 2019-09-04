#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct tcp_rpc_handshake_packet {TYPE_2__ peer_pid; int /*<<< orphan*/  sender_pid; } ;
struct tcp_rpc_data {int packet_num; scalar_t__ packet_type; int packet_len; int /*<<< orphan*/  remote_pid; } ;
struct raw_message {int dummy; } ;
struct process_id {int dummy; } ;
struct connection {int /*<<< orphan*/  our_port; int /*<<< orphan*/  our_ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  utime; int /*<<< orphan*/  pid; int /*<<< orphan*/  port; scalar_t__ ip; } ;

/* Variables and functions */
 TYPE_1__ PID ; 
 scalar_t__ RPC_HANDSHAKE ; 
 struct tcp_rpc_data* TCP_RPC_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ get_my_ipv4 () ; 
 int /*<<< orphan*/  init_server_PID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  matches_pid (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int rwm_fetch_data (struct raw_message*,struct tcp_rpc_handshake_packet*,int) ; 
 int /*<<< orphan*/  tcp_rpcs_send_handshake_error_packet (struct connection*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcp_rpcs_process_handshake_packet (struct connection *c, struct raw_message *msg) {
  struct tcp_rpc_data *D = TCP_RPC_DATA(c);
  static struct tcp_rpc_handshake_packet P;
  if (!PID.ip) {
    init_server_PID (c->our_ip, c->our_port);
    if (!PID.ip) {
      PID.ip = get_my_ipv4 ();
    }
  }
  if (D->packet_num != -1 || D->packet_type != RPC_HANDSHAKE) {
    return -2;
  }
  if (D->packet_len != sizeof (struct tcp_rpc_handshake_packet)) {
    tcp_rpcs_send_handshake_error_packet (c, -3);
    return -3;
  }
  assert (rwm_fetch_data (msg, &P, D->packet_len) == D->packet_len);
  memcpy (&D->remote_pid, &P.sender_pid, sizeof (struct process_id));
  if (!matches_pid (&PID, &P.peer_pid)) {
    vkprintf (1, "PID mismatch during handshake: local %08x:%d:%d:%d, remote %08x:%d:%d:%d\n",
                 PID.ip, PID.port, PID.pid, PID.utime, P.peer_pid.ip, P.peer_pid.port, P.peer_pid.pid, P.peer_pid.utime);
    tcp_rpcs_send_handshake_error_packet (c, -4);
    return -4;
  }
  return 0;
}