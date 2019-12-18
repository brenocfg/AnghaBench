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
struct rpc_update_stats {int /*<<< orphan*/  stats; int /*<<< orphan*/  id; } ;
struct long_update_stats {int dummy; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {scalar_t__ time_requested; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int get_node_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stats_time ; 
 int /*<<< orphan*/  long_stats ; 
 int long_stats_num ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* nodes ; 
 int nodes_num ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

int rpc_execute_update_stats (struct connection *c, struct rpc_update_stats *P, int len) {
  if (verbosity >= 2) {
    fprintf (stderr, "rpc_execute_update_stats: len = %d\n", len);
  }
  if (len != sizeof (struct rpc_update_stats)) {
    return 0;
  }
  int n = get_node_idx (P->id);
  if (n < 0) {
    return 0;
  }
  assert (0 <= n && n < nodes_num);
  nodes[n].time_requested = 0;
  long_stats_num = n;
  last_stats_time = now;
  memcpy (&long_stats, &P->stats, sizeof (struct long_update_stats));
  return 0;

}