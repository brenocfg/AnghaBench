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
typedef  union engine_stats {int dummy; } engine_stats ;
struct rpc_stats {int /*<<< orphan*/  stats; int /*<<< orphan*/  id; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_node_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* nodes ; 
 int nodes_num ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_execute_stats (struct connection *c, struct rpc_stats *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_stats: len = %d\n", len);
  }
  if (len != sizeof (struct rpc_stats)) {
    return 0;
  }
  int n = get_node_idx (P->id);
  if (n < 0) {
    return 0;
  }
  assert (0 <= n && n < nodes_num);
  memcpy (&nodes[n].stats, &P->stats, sizeof (union engine_stats));
  return 0;

}