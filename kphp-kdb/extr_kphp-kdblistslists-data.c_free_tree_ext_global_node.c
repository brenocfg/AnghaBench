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
typedef  int /*<<< orphan*/  tree_ext_global_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_global_nodes ; 
 int /*<<< orphan*/  tree_ext_global_node_size ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_tree_ext_global_node (tree_ext_global_t *T) {
  alloc_global_nodes--;
  zfree (T, tree_ext_global_node_size);
}