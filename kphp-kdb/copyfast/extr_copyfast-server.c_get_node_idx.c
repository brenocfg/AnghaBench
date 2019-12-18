#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int data; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  id_tree ; 
 TYPE_1__* tree_lookup (int /*<<< orphan*/ ,long long) ; 

int get_node_idx (long long id) {
  tree_t *T = tree_lookup (id_tree, id);
  if (T) {
    return T->data;
  }
  return -1;
}