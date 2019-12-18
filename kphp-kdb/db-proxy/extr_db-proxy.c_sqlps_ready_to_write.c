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
struct connection {int fd; struct conn_query* first_query; } ;
struct conn_query {TYPE_1__* cq_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wakeup ) (struct conn_query*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ proxy_watermark_query_type ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (struct conn_query*) ; 
 int verbosity ; 

int sqlps_ready_to_write (struct connection *c) {
  struct conn_query *q = c->first_query;

  if (verbosity > 1) {
    fprintf (stderr, "mysql server connection %d is ready to write\n", c->fd);
  }

  if (q != (struct conn_query *) c) {
    assert (q->cq_type == &proxy_watermark_query_type);
    q->cq_type->wakeup (q);
  }

  return 0;
}