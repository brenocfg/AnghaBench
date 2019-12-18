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
 int SIMPLIFY_TYPE_COUNT ; 
 int /*<<< orphan*/  antispam_db_request ; 
 int /*<<< orphan*/  heap_pattern ; 
 int /*<<< orphan*/  id_to_pattern ; 
 int /*<<< orphan*/  id_to_pattern_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_pattern_clear ; 
 int /*<<< orphan*/ * root ; 
 int /*<<< orphan*/  st_vec_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trie_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  triple_to_pattern ; 
 int /*<<< orphan*/  triple_to_patterns_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  triple_to_patterns_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void antispam_finish (void) {
  triple_to_patterns_foreach (triple_to_pattern, list_pattern_clear);
  id_to_pattern_clear (id_to_pattern);
  triple_to_patterns_clear (triple_to_pattern);

  int i;
  for (i = 0; i < SIMPLIFY_TYPE_COUNT; i++) {
    trie_free (root[i]);
  }

  st_vec_destroy (heap_pattern);
  st_vec_destroy (antispam_db_request);
}