#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_server {scalar_t__ inbound_packet_num; scalar_t__ port; int host; } ;
struct TYPE_5__ {scalar_t__ port; int ip; } ;
struct TYPE_4__ {scalar_t__ port; scalar_t__ ip; } ;
struct rpc_handshake {TYPE_2__ sender_pid; TYPE_1__ peer_pid; } ;
struct TYPE_6__ {scalar_t__ port; scalar_t__ ip; } ;

/* Variables and functions */
 TYPE_3__ PID ; 
 int /*<<< orphan*/  rpc_server_seterror (struct rpc_server*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpc_handshake_execute (struct rpc_server *server, char *answer, int answer_len) { /* {{{ */
  if (answer_len != sizeof (struct rpc_handshake) || server->inbound_packet_num != 0) {
    rpc_server_seterror (server, "Bad handshake packet", 0);
    return -1;
  }
  struct rpc_handshake *S = (void *)answer;
  if ((S->peer_pid.port != PID.port) || (S->peer_pid.ip != PID.ip && S->peer_pid.ip && PID.ip) || S->sender_pid.port != server->port || (S->sender_pid.ip != server->host && S->sender_pid.ip && server->host && server->host != 0x7f000001)) {
    rpc_server_seterror (server, "Bad pid in handshake packet", 0);
    return -1;
  }
  return 0;
}