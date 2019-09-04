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
struct conn_query {scalar_t__ outbound; } ;

/* Variables and functions */
 int insert_conn_query_into_list (struct conn_query*,struct conn_query*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,struct conn_query*) ; 

int insert_conn_query (struct conn_query *q) {
  vkprintf (2, "insert_conn_query(%p)\n", q);
  struct conn_query *h = (struct conn_query *) q->outbound;
  return insert_conn_query_into_list (q, h);
}