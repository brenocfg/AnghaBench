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
struct gather_data {char* orig_key; char* new_key; } ;
struct conn_query {int dummy; } ;

/* Variables and functions */
 struct gather_data* GATHER_QUERY (struct conn_query*) ; 
 int /*<<< orphan*/  delete_search_query (struct conn_query*) ; 
 int /*<<< orphan*/  end_search_query (struct conn_query*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  gather_timeouts ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int search_query_timeout (struct conn_query *q) {
  if (verbosity >= 3) {
    fprintf (stderr, "Query %p timeout.\n", q);
  }
  struct gather_data *G = GATHER_QUERY(q);
  fprintf (stderr, "Query on key %s (outbound key %s) timeout\n", G->orig_key, G->new_key);
  gather_timeouts++;
  end_search_query (q);
  delete_search_query (q);
  //query_complete (q->requester, 1);
  return 0;
}