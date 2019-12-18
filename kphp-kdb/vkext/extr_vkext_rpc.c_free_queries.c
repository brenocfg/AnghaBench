#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ qid; } ;

/* Variables and functions */
 int max_query_id ; 
 TYPE_1__* queries ; 
 int /*<<< orphan*/  rpc_query_delete (TYPE_1__*) ; 

void free_queries (void) {
  int i;
//  fprintf (stderr, "max_query_id = %d\n", max_query_id);
  for (i = 0; i < max_query_id; i++) if (queries[i].qid) {
    rpc_query_delete (&queries[i]);
  }
}