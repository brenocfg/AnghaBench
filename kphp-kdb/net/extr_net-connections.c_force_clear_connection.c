#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {scalar_t__ status; int flags; TYPE_2__* ev; TYPE_1__* type; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (struct connection*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int C_SPECIAL ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  clear_connection_timeout (struct connection*) ; 
 int /*<<< orphan*/  close_special_connection (struct connection*) ; 
 scalar_t__ conn_connecting ; 
 int /*<<< orphan*/  memset (struct connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  total_connect_failures ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ) ; 

int force_clear_connection (struct connection *c) {
  vkprintf (1, "socket %d: forced closing\n", c->fd);
  if (c->status != conn_connecting) {
    active_connections--;
    if (c->flags & C_SPECIAL) {
      close_special_connection (c);
    }
  } else {
    total_connect_failures++;
  }
  c->type->close (c, 0);
  clear_connection_timeout (c);

  if (c->ev) {
    c->ev->data = 0;
  }
  memset (c, 0, sizeof(struct connection));

  return 1;
}