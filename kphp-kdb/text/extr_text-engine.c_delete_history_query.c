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
struct conn_query {int /*<<< orphan*/  requester; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct conn_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pending_http_queries ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int delete_history_query (struct conn_query *q) {
  if (verbosity > 1) {
    fprintf (stderr, "delete_history_query(%p,%p)\n", q, q->requester);
  }

  pending_http_queries--;
  delete_conn_query (q);
  zfree (q, sizeof (*q));
  return 0;
}