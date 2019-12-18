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
struct TYPE_5__ {scalar_t__ item_id; scalar_t__ op; int priority; TYPE_3__* iter; int /*<<< orphan*/  cur; int /*<<< orphan*/  word; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ query_node_t ;
struct TYPE_6__ {int sp; scalar_t__ item_id; int cur_y; int /*<<< orphan*/  cur; } ;

/* Variables and functions */
 TYPE_3__* IHE ; 
 scalar_t__ MAX_ITEM_ID ; 
 scalar_t__ MAX_WORDS ; 
 scalar_t__ MIN_ITEM_ID ; 
 scalar_t__ Q_words ; 
 int /*<<< orphan*/  ihe_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qn_false ; 
 scalar_t__ qn_true ; 
 scalar_t__ qn_word ; 
 int /*<<< orphan*/  reoptimize_flag ; 
 int /*<<< orphan*/  universal_tag_hash ; 

int prepare_query_iterators (query_node_t *X) {
  int i;
  if (!X) {
    return 0;
  }
  if (prepare_query_iterators (X->left) < 0 ||
      prepare_query_iterators (X->right) < 0) {
    return -1;
  }
  X->item_id = (X->op == qn_false ? MAX_ITEM_ID : MIN_ITEM_ID);
  X->priority = 0;
  if (X->op == qn_true && !X->word) {
    X->word = universal_tag_hash;
  } else if (X->op != qn_word || X->iter) {
    return 0;
  }

  /*  --- the following optimization is incorrect in general ---
      i = add_query_word (X->word);
      if (i < 0) {
      return -1;
      }
   */
  if (Q_words >= MAX_WORDS) {
    return -1;
  }
  i = Q_words++;
  IHE[i].sp = -2;

  if (IHE[i].sp == -2) {
    ihe_init (IHE+i, X->word, 0, 0);
  }
  X->iter = &IHE[i];
  X->item_id = X->iter->item_id;
  X->cur = X->iter->cur;
  if (X->item_id == MAX_ITEM_ID) {
    reoptimize_flag++;
    X->op = qn_false;
  }
  X->priority = X->iter->cur_y & 1;
  return 1;
}