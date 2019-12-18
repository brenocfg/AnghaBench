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
typedef  int /*<<< orphan*/  stree_t ;

/* Variables and functions */
 int /*<<< orphan*/  online_tree_nodes ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void free_stree_node (stree_t *T) {
  --online_tree_nodes;
  zfree (T, sizeof (stree_t));
}