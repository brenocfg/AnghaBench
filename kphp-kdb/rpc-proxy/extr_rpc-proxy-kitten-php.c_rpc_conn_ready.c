#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connection {scalar_t__ status; scalar_t__ fd; } ;
struct TYPE_2__ {scalar_t__ packet_num; } ;

/* Variables and functions */
 TYPE_1__* RPCS_DATA (struct connection*) ; 
 scalar_t__ conn_reading_query ; 
 scalar_t__ conn_running ; 
 scalar_t__ cr_ok ; 
 int /*<<< orphan*/  server_check_ready (struct connection*) ; 

int rpc_conn_ready (struct connection *c) {
  server_check_ready (c);
  return c && (c->status == cr_ok || c->status == conn_running || c->status == conn_reading_query) && RPCS_DATA(c)->packet_num >= 0 && c->fd >= 0;
}