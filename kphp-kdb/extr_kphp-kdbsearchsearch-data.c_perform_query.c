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
 int FLAG_PRIORITY_SORT_SEARCH ; 
 scalar_t__ Q_hash_group_mode ; 
 scalar_t__ Q_min_priority ; 
 int Q_order ; 
 scalar_t__ Q_root ; 
 int /*<<< orphan*/  Q_words ; 
 int R_tot ; 
 int R_tot_groups ; 
 int /*<<< orphan*/  Root ; 
 int /*<<< orphan*/  clear_res () ; 
 int /*<<< orphan*/  fast_intersection_query () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  free_all_list_decoders () ; 
 scalar_t__ has_empty_range () ; 
 int perform_ext_query () ; 
 int /*<<< orphan*/  postprocess_res () ; 
 int /*<<< orphan*/  priority_sort_query () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ t_depth ; 
 scalar_t__ tree_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int perform_query (void) {
  int i;
  clear_res ();

  if ((!Q_words && !Q_root) || has_empty_range () )  {
    return 0;
  }

  if (verbosity > 1 && t_depth < 0) {
    t_depth = tree_depth (Root, 0);
    fprintf (stderr, "tree depth = %d\n", t_depth);
  }

  if (Q_root) {
    Q_min_priority = 0;
    i = perform_ext_query ();
    free_all_list_decoders ();
    return i;
  }

  vkprintf (3, "Q_order = %x\n", Q_order);
  if (Q_order & FLAG_PRIORITY_SORT_SEARCH) {
    priority_sort_query ();
  } else {
    fast_intersection_query ();
  }

  free_all_list_decoders ();
  postprocess_res ();
  return Q_hash_group_mode ? R_tot_groups : R_tot;
}