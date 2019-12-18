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
struct TYPE_4__ {struct conn_query* first_q; } ;
typedef  TYPE_1__ user_t ;
struct conn_query {struct conn_query* next; } ;

/* Variables and functions */
 struct conn_query* USER_CONN (TYPE_1__*) ; 
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  pending_http_queries ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int process_user_query_queue (user_t *U) {
  struct conn_query *tmp, *tnext;

  for (tmp = U->first_q; tmp != USER_CONN (U); tmp = tnext) {
    tnext = tmp->next;
    //fprintf (stderr, "scanning user history queue %p,next = %p\n", tmp, tnext);
    pending_http_queries--;
    delete_conn_query (tmp);
    zfree (tmp, sizeof (*tmp));
  }

  return 0;
}