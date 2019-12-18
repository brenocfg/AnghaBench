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
 int /*<<< orphan*/  tree ; 
 int tree_lookup_all_next (int /*<<< orphan*/ ,char const*,int,int,int,int,int) ; 

int get_all_next_entries (const char *key, int key_len, int prefix_len, int strict) {
  return tree_lookup_all_next (tree, key, key_len, prefix_len, strict, 1, 1);
}