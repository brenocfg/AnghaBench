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
typedef  int /*<<< orphan*/  var_ltree_x_t ;
typedef  int /*<<< orphan*/  object_id_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  combine_ltree_x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ignore_tree ; 
 int /*<<< orphan*/  lrand48 () ; 
 int /*<<< orphan*/  ltree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ignore_list_object_add (list_id_t list_id, object_id_t object_id) {
  static var_ltree_x_t lkey;
  combine_ltree_x (list_id, object_id, &lkey);
  ignore_tree = ltree_insert (ignore_tree, lkey, lrand48 ());
}