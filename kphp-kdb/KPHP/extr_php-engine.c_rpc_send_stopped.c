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
struct connection {scalar_t__ our_port; scalar_t__ our_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_STOP_READY ; 
 int pid ; 
 int /*<<< orphan*/  ready_cnt ; 
 int /*<<< orphan*/  send_rpc_query (struct connection*,int /*<<< orphan*/ ,int,int*,int) ; 
 int start_time ; 
 int worker_id ; 

void rpc_send_stopped (struct connection *c) {
  int q[100], qn = 0;
  qn += 2;
  q[qn++] = -1;
  q[qn++] = (int)c->our_ip; // addr
  q[qn++] = (int)c->our_port; // port
  q[qn++] = pid; // pid
  q[qn++] = start_time; // start_time
  q[qn++] = worker_id; // id
  q[qn++] = ready_cnt++; // ready_cnt
  qn++;
  send_rpc_query (c, RPC_STOP_READY, -1, q, qn * 4);
}