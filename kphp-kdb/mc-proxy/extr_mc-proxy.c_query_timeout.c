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
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct conn_target {int /*<<< orphan*/  port; TYPE_1__ target; } ;
struct conn_query {TYPE_2__* outbound; } ;
struct TYPE_4__ {int unreliability; int fd; struct conn_target* target; } ;

/* Variables and functions */
 int /*<<< orphan*/  expired_forwarded_queries ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct conn_query*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  store_expired_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

int query_timeout (struct conn_query *q) {
  q->outbound->unreliability += 1000;
  if (verbosity > 0) {
    fprintf (stderr, "query %p of connection %p (fd=%d) timed out, unreliability=%d\n", q, q->outbound, q->outbound->fd, q->outbound->unreliability);
  }
  expired_forwarded_queries++;

  struct conn_target *S = q->outbound->target;
  store_expired_target (ntohl (S->target.s_addr), S->port);

  return 0;
}