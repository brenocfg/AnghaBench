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
struct raw_message {int dummy; } ;
struct connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int rwm_create (struct raw_message*,void*,int) ; 
 int /*<<< orphan*/  tcp_rpc_conn_send (struct connection*,struct raw_message*,int /*<<< orphan*/ ) ; 

void tcp_rpc_conn_send_data (struct connection *c, int len, void *Q) {
  assert (!(len & 3));
  struct raw_message r;
  assert (rwm_create (&r, Q, len) == len);
  tcp_rpc_conn_send (c, &r, 0);
}