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
struct mult_iterator {scalar_t__ pos; int /*<<< orphan*/  (* jump_to ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct lev_delete_group {int group_id; } ;
typedef  int /*<<< orphan*/  iterator_t ;

/* Variables and functions */
 scalar_t__ INFTY ; 
 unsigned int MAX_USERS ; 
 scalar_t__* R ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ build_word_iterator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_tmp_word_data () ; 
 int /*<<< orphan*/  delete_single_user_group_fast (scalar_t__,int) ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  field_value_hash (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_word_count_nomult (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_grp_id ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int delete_group (struct lev_delete_group *E) {
  int group_id = E->group_id, num = 0, i;

  clear_tmp_word_data ();

  if (get_word_count_nomult (field_value_hash (q_grp_id, group_id))) {
    dyn_mark (0);
    struct mult_iterator *I = (struct mult_iterator *) build_word_iterator (field_value_hash (q_grp_id, group_id));
    while (I->pos < INFTY) {
      R[num++] = I->pos;
      I->jump_to ((iterator_t)I, I->pos + 1);
    }
    dyn_release (0);
    assert ((unsigned)num <= MAX_USERS);
    for (i = 0; i < num; i++) {
      delete_single_user_group_fast (R[i], group_id);
    }
  }

  return 1; // does now work
}