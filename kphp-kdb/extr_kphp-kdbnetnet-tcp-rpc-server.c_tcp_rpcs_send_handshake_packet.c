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
struct tcp_rpc_handshake_packet {int /*<<< orphan*/  peer_pid; int /*<<< orphan*/  sender_pid; scalar_t__ flags; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct tcp_rpc_data {TYPE_1__ remote_pid; } ;
struct process_id {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* flush_packet ) (struct connection*) ;} ;
typedef  int /*<<< orphan*/  P ;

/* Variables and functions */
 TYPE_1__ PID ; 
 int /*<<< orphan*/  RPC_HANDSHAKE ; 
 TYPE_2__* TCP_RPCS_FUNC (struct connection*) ; 
 struct tcp_rpc_data* TCP_RPC_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (struct tcp_rpc_handshake_packet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int /*<<< orphan*/  tcp_rpc_conn_send_data (struct connection*,int,struct tcp_rpc_handshake_packet*) ; 

__attribute__((used)) static int tcp_rpcs_send_handshake_packet (struct connection *c) {
  struct tcp_rpc_data *D = TCP_RPC_DATA(c);
  static struct tcp_rpc_handshake_packet P;
  assert (PID.pid);
  memset (&P, 0, sizeof (P));
  P.type = RPC_HANDSHAKE;
  P.flags = 0;
  memcpy (&P.sender_pid, &PID, sizeof (struct process_id));
  memcpy (&P.peer_pid, &D->remote_pid, sizeof (struct process_id));

  tcp_rpc_conn_send_data (c, sizeof (P), &P);
  
  TCP_RPCS_FUNC(c)->flush_packet (c);
  return 0;
}