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
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPYEXEC_RPC_TYPE_PING ; 
 int /*<<< orphan*/  Q ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  ping_sent_time ; 
 int /*<<< orphan*/ * rpc_create_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct connection*,int /*<<< orphan*/ ) ; 
 int rpc_send_query (int /*<<< orphan*/ ,struct connection*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int rpc_send_ping (struct connection *c) {
  vkprintf (3, "rpc_send_ping (c: %p)\n", c);
  if (rpc_create_query (Q, 0, c, COPYEXEC_RPC_TYPE_PING) == NULL) {
    vkprintf (2, "rpc_send_ping: rpc_create_query returns NULL.\n");
    return -__LINE__;
  }
  ping_sent_time = now;
  return rpc_send_query (Q, c);
}