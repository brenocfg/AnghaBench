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
struct connection {int /*<<< orphan*/  status; scalar_t__ pending_queries; scalar_t__ generation; } ;
struct conn_query_functions {int dummy; } ;
struct aio_connection {int dummy; } ;

/* Variables and functions */
 scalar_t__ conn_generation ; 
 int /*<<< orphan*/  conn_wait_aio ; 
 int /*<<< orphan*/  create_aio_query (struct aio_connection*,struct connection*,double,struct conn_query_functions*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct aio_connection*,struct connection*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int conn_schedule_aio (struct aio_connection *a, struct connection *c, double timeout, struct conn_query_functions *cq) {
  if (verbosity > 1) {
    fprintf (stderr, "in conn_schedule_aio(%p,%p)\n", a, c);
  }

  c->generation = ++conn_generation;
  c->pending_queries = 0;
  create_aio_query (a, c, timeout, cq);
  c->status = conn_wait_aio;

  return -1;
}