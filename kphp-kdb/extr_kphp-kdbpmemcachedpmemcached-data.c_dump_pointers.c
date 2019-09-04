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
typedef  int /*<<< orphan*/  hash_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  tree ; 
 int tree_dump_pointers (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int) ; 

int dump_pointers (hash_entry_t **x, int p, int maxp) {
  return tree_dump_pointers (tree, x, p, maxp);
}