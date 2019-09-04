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

/* Variables and functions */
 scalar_t__ Q_hash_group_mode ; 
 int /*<<< orphan*/  Q_words ; 
 int R_tot ; 
 int R_tot_groups ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  clear_res () ; 
 int /*<<< orphan*/  free_all_list_decoders () ; 
 scalar_t__ has_empty_range () ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 int /*<<< orphan*/  postprocess_res () ; 
 int /*<<< orphan*/  ranking_query () ; 
 int tree_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbosity ; 

int perform_query (void) {
  clear_res ();

  if (!Q_words || has_empty_range () )  {
    return 0;
  }

  if (verbosity >= 3) {
    int t_depth = tree_depth (Root, 0);
    kprintf ("tree depth = %d\n", t_depth);
  }

  ranking_query ();

  free_all_list_decoders ();
  postprocess_res ();
  return Q_hash_group_mode ? R_tot_groups : R_tot;
}