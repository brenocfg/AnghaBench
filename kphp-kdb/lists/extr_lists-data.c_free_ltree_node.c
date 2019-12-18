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
typedef  int /*<<< orphan*/  ltree_t ;

/* Variables and functions */
 scalar_t__ alloc_ltree_nodes ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ltree_node_size ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ltree_node (ltree_t *T) {
  assert (--alloc_ltree_nodes >= 0);
  zfree (T, ltree_node_size);
}