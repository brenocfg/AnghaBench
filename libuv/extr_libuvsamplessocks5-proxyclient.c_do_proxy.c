#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  incoming; int /*<<< orphan*/  outgoing; } ;
typedef  TYPE_1__ client_ctx ;

/* Variables and functions */
 scalar_t__ conn_cycle (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int do_kill (TYPE_1__*) ; 
 int s_proxy ; 

__attribute__((used)) static int do_proxy(client_ctx *cx) {
  if (conn_cycle("client", &cx->incoming, &cx->outgoing)) {
    return do_kill(cx);
  }

  if (conn_cycle("upstream", &cx->outgoing, &cx->incoming)) {
    return do_kill(cx);
  }

  return s_proxy;
}