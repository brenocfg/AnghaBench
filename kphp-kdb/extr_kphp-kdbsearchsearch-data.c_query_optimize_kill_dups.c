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
 int /*<<< orphan*/  Q_root ; 
 int /*<<< orphan*/  query_convert_to_cumulatative_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query_kill_duplicate_words (int /*<<< orphan*/ ) ; 
 scalar_t__ tot_query_nodes_kill_dup ; 
 scalar_t__ tot_query_nodes_list ; 

__attribute__((used)) static void query_optimize_kill_dups (void) {
  tot_query_nodes_kill_dup = tot_query_nodes_list = 0;
  query_convert_to_cumulatative_expression (Q_root);
  Q_root = query_kill_duplicate_words (Q_root);
}