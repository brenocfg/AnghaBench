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
typedef  int /*<<< orphan*/  tree_var_value_t ;
struct tl_combinator_tree {scalar_t__ act; scalar_t__ type; scalar_t__ type_len; scalar_t__ type_flags; void* data; struct tl_combinator_tree* right; struct tl_combinator_tree* left; } ;

/* Variables and functions */
 scalar_t__ act_var ; 
 int /*<<< orphan*/  assert (int) ; 
 struct tl_combinator_tree* tl_get_var_value (int /*<<< orphan*/ **,void*) ; 
 scalar_t__ tl_get_var_value_num (int /*<<< orphan*/ **,void*) ; 
 int /*<<< orphan*/  tl_set_var_value (int /*<<< orphan*/ **,void*,struct tl_combinator_tree*) ; 
 int /*<<< orphan*/  tl_set_var_value_num (int /*<<< orphan*/ **,void*,struct tl_combinator_tree*,long long) ; 
 int tl_tree_lookup_value (struct tl_combinator_tree*,void*,int /*<<< orphan*/ **) ; 
 int tl_tree_lookup_value_nat (struct tl_combinator_tree*,void*,long long,int /*<<< orphan*/ **) ; 
 scalar_t__ type_num ; 
 scalar_t__ type_num_value ; 
 scalar_t__ type_type ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int uniformize (struct tl_combinator_tree *L, struct tl_combinator_tree *R, tree_var_value_t **T) {
  if (!L || !R) {
    assert (!L && !R);
    return 1;
  }
  if (R->act == act_var) {
    struct tl_combinator_tree *_ = R; R = L; L = _;
  }
 
  if (L->type == type_type) {
    if (R->type != type_type || L->type_len != R->type_len || L->type_flags != R->type_flags) {
      vkprintf (3, "Type mistmatch. Error\n");
      return 0;
    }
    if (R->data == (void *)-1l || L->data == (void *)-1l) { return 1;}
    if (L->act == act_var) {
      int x = tl_tree_lookup_value (R, L->data, T);
      if (x > 0) {
//      if (tl_tree_lookup_value (R, L->data, T) > 0) {
        vkprintf (3, "Circular reference. Error\n");
        return 0;
      }
      if (x == 0) {
        return 1;
      }
      struct tl_combinator_tree *E = tl_get_var_value (T, L->data);
      if (!E) {
        tl_set_var_value (T, L->data, R);
        return 1;
      } else {
        return uniformize (E, R, T);
      }
    } else {
      if (L->act != R->act || L->data != R->data) {
        vkprintf (3, "Type mistmatch. Error\n");
        return 0;
      }
      return uniformize (L->left, R->left, T) && uniformize (L->right, R->right, T);
    }
  } else {
    assert (L->type == type_num || L->type == type_num_value);
    if (R->type != type_num && R->type != type_num_value) {
      vkprintf (3, "Type mistmatch. Error\n");
      return 0;
    }
    assert (R->type == type_num || R->type == type_num_value);
    if (R->data == (void *)-1l || L->data == (void *)-1l) { return 1;}
    long long x = 0;
    struct tl_combinator_tree *K = L;
    while (1) {
      x += K->type_flags;
      if (K->type == type_num_value) {
        break;
      }
      if (!tl_get_var_value (T, K->data)) {
        int s = tl_tree_lookup_value_nat (R, K->data, K->type_flags, T);
        if (s > 0) {
          vkprintf (3, "Circular reference. Error\n");
          return 0;
        }
        if (s == 0) {
          return 1;
        }
        /*tl_set_var_value_num (T, K->data, R, -x);
        return 1;*/
        break;
      }
      x += tl_get_var_value_num (T, K->data);
      K = tl_get_var_value (T, K->data);
    }
    long long y = 0;
    struct tl_combinator_tree *M = R;
    while (1) {
      y += M->type_flags;
      if (M->type == type_num_value) {
        break;
      }
      if (!tl_get_var_value (T, M->data)) {
        int s = tl_tree_lookup_value_nat (L, M->data, M->type_flags, T);
        if (s > 0) {
          vkprintf (3, "Circular reference. Error\n");
          return 0;
        }
        if (s == 0) {
          return 1;
        }
        /*tl_set_var_value_num (T, M->data, L, -y);
        return 1;*/
        break;
      }
      y += tl_get_var_value_num (T, M->data);
      M = tl_get_var_value (T, M->data);
    }
    if (K->type == type_num_value && M->type == type_num_value) {
      return x == y;     
    }
    if (M->type == type_num_value) {
      tl_set_var_value_num (T, K->data, M, -(x - y + M->type_flags));
      return 1;     
    } else if (K->type == type_num_value) {
      tl_set_var_value_num (T, M->data, K, -(y - x + K->type_flags));
      return 1;     
    } else {
      if (x >= y) {
        tl_set_var_value_num (T, K->data, M, -(x - y + M->type_flags));
      } else {
        tl_set_var_value_num (T, M->data, K, -(y - x + K->type_flags));
      }
      return 1;
    }
  }
  return 0;
}