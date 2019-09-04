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
struct connection {scalar_t__ generation; struct conn_query* first_query; } ;
struct conn_query {scalar_t__ req_generation; struct conn_query* next; scalar_t__ extra; struct connection* requester; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct conn_query*) ; 

int check_gather_query (struct connection *c, struct conn_query *qu) {
  struct connection *C = qu->requester;
  struct conn_query *Q = C->first_query;
  if (C->generation != qu->req_generation) {
    return 0;
  }
  while (Q != (struct conn_query*)C) {
    assert (Q);
    if (Q == (struct conn_query *)(qu->extra)) {
      return 1;
    }
    Q = Q->next;
  }
  return 0;
}