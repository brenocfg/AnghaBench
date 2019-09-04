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
struct conn_query {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GATHER_QUERY (struct conn_query*) ; 
 int /*<<< orphan*/  delete_conn_query (struct conn_query*) ; 
 int /*<<< orphan*/  free_gather (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct conn_query*,int) ; 

int delete_search_query (struct conn_query *q) {
  free_gather (GATHER_QUERY(q));
  delete_conn_query (q);
  zfree (q, sizeof (*q));
  return 0;
}