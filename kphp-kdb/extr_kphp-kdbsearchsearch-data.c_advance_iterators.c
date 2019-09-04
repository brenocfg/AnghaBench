#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ item_id; int op; int priority; int /*<<< orphan*/  cur; struct TYPE_5__* right; struct TYPE_5__* left; TYPE_2__* iter; } ;
typedef  TYPE_1__ query_node_t ;
struct TYPE_6__ {int cur_y; long long item_id; int /*<<< orphan*/  cur; } ;
typedef  TYPE_2__ iheap_en_t ;

/* Variables and functions */
 scalar_t__ MAX_ITEM_ID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ihe_skip_advance (TYPE_2__*,long long) ; 
#define  qn_and 133 
#define  qn_false 132 
#define  qn_minus 131 
#define  qn_or 130 
#define  qn_true 129 
#define  qn_word 128 
 int /*<<< orphan*/  reoptimize_flag ; 

long long advance_iterators (query_node_t *X, long long min_item_id) {
  iheap_en_t *A;
  query_node_t *Y, *Z;
  if (X->item_id == MAX_ITEM_ID) {
    return X->item_id;
  }
  switch (X->op) {
    case qn_false:
      X->cur = 0;
      return MAX_ITEM_ID;
    case qn_true:
    case qn_word:
      A = X->iter;
      if (!ihe_skip_advance (A, min_item_id)) {
        X->op = qn_false;
        X->priority = 0;
        reoptimize_flag++;
        X->cur = 0;
        return X->item_id = MAX_ITEM_ID;
      }
      X->priority = A->cur_y & 1;
      X->cur = A->cur;
      return X->item_id = A->item_id;
    case qn_and:
      Y = X->left; Z = X->right;
      if (Y->item_id < min_item_id) {
        if (MAX_ITEM_ID == advance_iterators (Y, min_item_id)) { return X->item_id = MAX_ITEM_ID; }
      }

      while (Y->item_id != Z->item_id) {
        if (Y->item_id < Z->item_id) {
          if (MAX_ITEM_ID == advance_iterators (Y, Z->item_id)) { return X->item_id = MAX_ITEM_ID; }
        } else {
          if (MAX_ITEM_ID == advance_iterators (Z, Y->item_id)) { return X->item_id = MAX_ITEM_ID; }
        }
      }
      X->cur = Y->cur;
      X->priority = Y->priority + Z->priority;
      return X->item_id = Y->item_id;
    case qn_or:
      Y = X->left; Z = X->right;
      if (Y->item_id < min_item_id) {
        advance_iterators (Y, min_item_id);
      }
      if (Z->item_id < min_item_id) {
        advance_iterators (Z, min_item_id);
      }
      if (Y->item_id < Z->item_id) {
        X->priority = Y->priority;
        X->cur = Y->cur;
        return X->item_id = Y->item_id;
      } else if (Y->item_id > Z->item_id) {
        X->priority = Z->priority;
        X->cur = Z->cur;
        return X->item_id = Z->item_id;
      }
      X->cur = Y->cur;
      X->priority = Y->priority + Z->priority;
      return X->item_id = Y->item_id;
    case qn_minus:
      Y = X->left; Z = X->right;
      if (Y->item_id < min_item_id) {
        if (MAX_ITEM_ID == advance_iterators (Y, min_item_id)) { return X->item_id = MAX_ITEM_ID; }
      }

      if (Y->item_id > Z->item_id) {
        advance_iterators (Z, Y->item_id);
      }
      while (Y->item_id == Z->item_id && Y->item_id < MAX_ITEM_ID) {
        if (MAX_ITEM_ID == advance_iterators (Y, Y->item_id + 1)) {
          return X->item_id = MAX_ITEM_ID;
        }
        advance_iterators (Z, Y->item_id);
      }
      X->priority = Y->priority;
      X->cur = Y->cur;
      return X->item_id = Y->item_id;
    default:
      assert (0);
  }
}