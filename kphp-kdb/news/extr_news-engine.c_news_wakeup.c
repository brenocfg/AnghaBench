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
struct TYPE_2__ {scalar_t__ total_bytes; } ;
struct connection {int /*<<< orphan*/  flags; TYPE_1__ Out; int /*<<< orphan*/  status; scalar_t__ pending_queries; scalar_t__ generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_WANTWR ; 
 int /*<<< orphan*/  clear_connection_timeout (struct connection*) ; 
 scalar_t__ conn_generation ; 
 int /*<<< orphan*/  conn_reading_query ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int news_wakeup (struct connection *c) {

  if (verbosity > 1) {
    fprintf (stderr, "news_wakeup (%p)\n", c);
  }

  c->generation = ++conn_generation;
  c->pending_queries = 0;
  c->status = conn_reading_query;

  clear_connection_timeout (c);

  if (c->Out.total_bytes > 0) {
    c->flags |= C_WANTWR;
  }

  return 0;
}