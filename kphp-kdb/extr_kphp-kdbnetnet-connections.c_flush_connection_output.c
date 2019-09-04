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
struct connection {int flags; int /*<<< orphan*/  fd; TYPE_1__* type; } ;
struct TYPE_2__ {int (* writer ) (struct connection*) ;} ;

/* Variables and functions */
 int C_INCONN ; 
 int C_WANTWR ; 
 int /*<<< orphan*/  compute_conn_events (struct connection*) ; 
 int /*<<< orphan*/  epoll_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ out_total_processed_bytes (struct connection*) ; 
 scalar_t__ out_total_unprocessed_bytes (struct connection*) ; 
 int stub1 (struct connection*) ; 

int flush_connection_output (struct connection *c) {
  if (out_total_processed_bytes (c) + out_total_unprocessed_bytes (c) > 0) {
    c->flags |= C_WANTWR;
    int res = c->type->writer (c);
    if (out_total_processed_bytes (c) > 0 && !(c->flags & C_INCONN)) {
      epoll_insert (c->fd, compute_conn_events (c));
    }
    return res;
  } else {
    return 0;
  }
}