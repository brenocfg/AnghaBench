#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int op; struct TYPE_4__* left; struct TYPE_4__* right; int /*<<< orphan*/  priority; } ;
typedef  TYPE_1__ query_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  qn_and 133 
#define  qn_false 132 
#define  qn_minus 131 
#define  qn_or 130 
#define  qn_true 129 
#define  qn_word 128 

query_node_t *optimize_query (query_node_t *X) {
  if (!X) {
    return 0;
  }
  X->left = optimize_query (X->left);
  X->right = optimize_query (X->right);
  switch (X->op) {
    case qn_false:
    case qn_true:
    case qn_word:
      return X;
    case qn_and:
      if (X->left->op == qn_false) {
        return X->left;
      }
      if (X->left->op == qn_true) {
        return X->right;
      }
      if (X->right->op == qn_false) {
        return X->right;
      }
      if (X->right->op == qn_true) {
        return X->left;
      }
      return X;
    case qn_or:
      if (X->left->op == qn_true) {
        return X->left;
      }
      if (X->left->op == qn_false) {
        return X->right;
      }
      if (X->right->op == qn_true) {
        return X->right;
      }
      if (X->right->op == qn_false) {
        return X->left;
      }
      return X;
    case qn_minus:
      if (X->left->op == qn_false) {
        return X->left;
      }
      if (X->right->op == qn_true) {
        X->op = qn_false;
        X->left = X->right = 0;
        X->priority = 0;
        return X;
      }
      if (X->right->op == qn_false) {
        return X->left;
      }
      return X;
  }
  assert (0);
}