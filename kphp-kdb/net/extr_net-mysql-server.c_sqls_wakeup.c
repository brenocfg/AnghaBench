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
struct TYPE_3__ {scalar_t__ total_bytes; } ;
struct connection {int fd; int status; scalar_t__ pending_queries; scalar_t__ generation; int /*<<< orphan*/  flags; TYPE_1__ Out; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sql_wakeup ) (struct connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  C_WANTWR ; 
 TYPE_2__* SQLS_FUNC (struct connection*) ; 
 scalar_t__ conn_expect_query ; 
 scalar_t__ conn_generation ; 
 scalar_t__ conn_wait_net ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct connection*) ; 
 int verbosity ; 

__attribute__((used)) static int sqls_wakeup (struct connection *c) {
  if (verbosity > 1) {
    fprintf (stderr, "sqls_wakeup for #%d: status=%d\n", c->fd, c->status);
  }
  if (c->status == conn_wait_net) {
    SQLS_FUNC(c)->sql_wakeup (c);
    if (c->status == conn_wait_net) {
      c->status = conn_expect_query;
    }
  }
  if (c->Out.total_bytes > 0) {
    c->flags |= C_WANTWR;
  }
  c->generation = ++conn_generation;
  c->pending_queries = 0;
  return 0;
}