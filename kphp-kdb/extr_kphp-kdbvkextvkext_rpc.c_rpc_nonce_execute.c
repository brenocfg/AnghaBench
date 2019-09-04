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
struct rpc_server {int inbound_packet_num; } ;
struct rpc_nonce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_server_seterror (struct rpc_server*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpc_nonce_execute (struct rpc_server *server, char *answer, int answer_len) { /* {{{ */
  if (answer_len != sizeof (struct rpc_nonce) || server->inbound_packet_num != -1) {    
    rpc_server_seterror (server, "Bad nonce packet", 0);
    return -1;
  }
  return 0;
}