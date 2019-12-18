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
struct item {int key_len; scalar_t__ prev_time; scalar_t__ next_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  item_tree ; 
 struct item* tree_lookup (int /*<<< orphan*/ ,int,int const*) ; 

struct item *preload_key (int key_len, const int *key, int force) {
  struct item *I = tree_lookup (item_tree, key_len, key);
  if (I) { return I; }
  static struct item T;
  I = &T;
  I->key_len = -1;
  I->next_time = I->prev_time = 0;
  return I;
}