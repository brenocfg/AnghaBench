#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_var_value_t ;
struct tree {scalar_t__ type; int nc; TYPE_1__** c; } ;
struct tl_constructor {char* id; int /*<<< orphan*/  name; int /*<<< orphan*/  real_id; scalar_t__ right; scalar_t__ left; int /*<<< orphan*/  type; } ;
struct tl_combinator_tree {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 scalar_t__ L ; 
 scalar_t__ R ; 
 int /*<<< orphan*/  TL_ERROR (char*,...) ; 
 int /*<<< orphan*/  TL_FAIL ; 
 int /*<<< orphan*/  TL_INIT (scalar_t__) ; 
 scalar_t__ X ; 
 scalar_t__ Z ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  buf_pos ; 
 scalar_t__ change_first_var (scalar_t__,struct tl_combinator_tree**,scalar_t__) ; 
 int /*<<< orphan*/  change_var_ptrs (scalar_t__,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct tl_constructor* tl_add_constructor (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct tl_constructor* tl_add_function (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tl_buf_add_tree (scalar_t__,int) ; 
 int /*<<< orphan*/  tl_buf_reset () ; 
 int /*<<< orphan*/  tl_count_combinator_name (struct tl_constructor*) ; 
 struct tl_constructor* tl_get_constructor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tl_constructor* tl_get_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tl_parse_any_term (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_print_combinator (struct tl_constructor*) ; 
 scalar_t__ tl_tree_dup (scalar_t__) ; 
 int /*<<< orphan*/ * tree_clear_var_value (int /*<<< orphan*/ *) ; 
 scalar_t__ type_partial_comb_app_decl ; 
 int /*<<< orphan*/  zstrdup (char*) ; 

int tl_parse_partial_comb_app_decl (struct tree *T, int fun) {
  assert (T->type == type_partial_comb_app_decl);

  struct tl_constructor *c = !fun ? tl_get_constructor (T->c[0]->text, T->c[0]->len) : tl_get_function (T->c[0]->text, T->c[0]->len);
  if (!c) {
    TL_ERROR ("Can not make partial app for undefined combinator\n");
    return 0;
  }

  //TL_INIT (K);
  //static char buf[1000];
  //int x = sprintf (buf, "%s", c->id);
  TL_INIT (L);
  TL_INIT (R);
  L = tl_tree_dup (c->left);
  R = tl_tree_dup (c->right);
 
 
  tree_var_value_t *V = 0;
  change_var_ptrs (c->left, L, &V);
  change_var_ptrs (c->right, R, &V);
  V = tree_clear_var_value (V);

  int i;
  tl_buf_reset ();
  for (i = 1; i < T->nc; i++) {
    TL_INIT (X);
    TL_INIT (Z);
    X = tl_parse_any_term (T->c[i], 0);
    struct tl_combinator_tree *K = 0;
    if (!(Z = change_first_var (L, &K, X))) {    
      TL_FAIL;
    }
    L = Z;
    if (!K) {
      TL_ERROR ("Partial app: not enougth variables (i = %d)\n", i);
      TL_FAIL;
    }
    if (!(Z = change_first_var (R, &K, X))) {
      TL_FAIL;
    }
    assert (Z == R);
    tl_buf_add_tree (X, 1);
  }

  static char _buf[100000];
  snprintf (_buf, 100000, "%s%.*s", c->id, buf_pos, buf);
//  fprintf (stderr, "Local id: %s\n", _buf);

  struct tl_constructor *r = !fun ? tl_add_constructor (c->type, _buf, strlen (_buf), 1) : tl_add_function (c->type, _buf, strlen (_buf), 1);
  r->left = L;
  r->right = R;
  snprintf (_buf, 100000, "%s", c->id);
  r->real_id = zstrdup (_buf);
  if (!r->name) {
    tl_count_combinator_name (r);
  }
  tl_print_combinator (r);
  return 1;
}