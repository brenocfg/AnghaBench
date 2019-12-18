#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  var_ltree_x_t ;
struct TYPE_5__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ tree_ext_small_t ;
struct tree_payload {int flags; int /*<<< orphan*/  global_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  list_id; } ;

/* Variables and functions */
 struct tree_payload* LPAYLOAD (TYPE_1__*) ; 
 TYPE_3__* M_List ; 
 int /*<<< orphan*/  combine_ltree_x (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_list_entry_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int f_and_c ; 
 int /*<<< orphan*/  f_cnt ; 
 int f_xor_c ; 
 int /*<<< orphan*/  ltree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_tree ; 
 int /*<<< orphan*/  tot_list_entries ; 

__attribute__((used)) static int tree_delete_sublist (tree_ext_small_t *T) {
  struct tree_payload *P = LPAYLOAD (T);
  if (!((P->flags ^ f_xor_c) & f_and_c)) {
    delete_list_entry_aux (T->x, P->global_id, P->flags);
    static var_ltree_x_t ltree_key;
    combine_ltree_x (M_List->list_id, T->x, &ltree_key);
    object_tree = ltree_delete (object_tree, ltree_key);
    tot_list_entries--;
    f_cnt++;
    return 0; // delete this
  } else {
    return 1; // do not touch
  }
}