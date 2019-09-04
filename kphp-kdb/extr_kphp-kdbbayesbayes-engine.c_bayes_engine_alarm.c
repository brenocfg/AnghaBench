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
struct connection {int fd; int pending_queries; int status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_INTIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int bayes_engine_wakeup (struct connection*) ; 
 scalar_t__ conn_wait_aio ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int bayes_engine_alarm (struct connection *c) {
  if (verbosity > 1) {
    fprintf (stderr, "bayes_engine connection %d timeout alarm, %d queries pending, status=%d\n", c->fd, c->pending_queries, c->status);
  }
  assert (c->status == conn_wait_aio);
  c->flags |= C_INTIMEOUT;
  return bayes_engine_wakeup (c);
}