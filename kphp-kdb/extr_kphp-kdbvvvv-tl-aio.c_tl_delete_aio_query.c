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
struct conn_query {scalar_t__ start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  active_aio_queries ; 
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct conn_query*,double) ; 
 double get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 double total_aio_time ; 
 int verbosity ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int tl_delete_aio_query (struct conn_query *q) {
  if (q->start_time > 0) {
    double q_time = get_utime (CLOCK_MONOTONIC) - q->start_time;
    total_aio_time += q_time;
    if (verbosity > 1) {
      fprintf (stderr, "delete_aio_query(%p): query time %.6f\n", q, q_time);
    }
  }
  active_aio_queries--;
  delete_conn_query (q);
  zfree (q, sizeof (struct conn_query));
  return 0;
}