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
struct rpc_server {int inbound_packet_num; int packet_num; int /*<<< orphan*/  out_buf; int /*<<< orphan*/  out_rptr; int /*<<< orphan*/  out_wptr; scalar_t__ in_bytes; } ;

/* Variables and functions */

__attribute__((used)) static void rpc_server_clean (struct rpc_server *server) { /* {{{ */
  server->in_bytes = 0;
  server->out_wptr = server->out_rptr = server->out_buf;
  server->inbound_packet_num = server->packet_num = -2;
}