#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ sa_family; } ;
struct TYPE_8__ {TYPE_4__ addr; int /*<<< orphan*/  connect_req; } ;
struct TYPE_7__ {int /*<<< orphan*/  tcp; } ;
struct TYPE_9__ {TYPE_2__ t; TYPE_1__ handle; } ;
typedef  TYPE_3__ conn ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  conn_connect_done ; 
 int /*<<< orphan*/  conn_timer_reset (TYPE_3__*) ; 
 int uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int conn_connect(conn *c) {
  ASSERT(c->t.addr.sa_family == AF_INET ||
         c->t.addr.sa_family == AF_INET6);
  conn_timer_reset(c);
  return uv_tcp_connect(&c->t.connect_req,
                        &c->handle.tcp,
                        &c->t.addr,
                        conn_connect_done);
}