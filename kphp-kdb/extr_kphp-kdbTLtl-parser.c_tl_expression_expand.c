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
struct tl_token {int /*<<< orphan*/  text; struct tl_token* next; } ;
struct tl_expression {scalar_t__ type; int flag_expanded; struct tl_token* right; int /*<<< orphan*/  right_name; struct tl_token* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cstr_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cstr_join_with_sugar (struct tl_token*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tl_token* tl_token_clone (struct tl_token*) ; 
 scalar_t__ tlet_polymorphic ; 
 scalar_t__ tlet_polymorphic_instance ; 
 scalar_t__ tlet_simple ; 

void tl_expression_expand (struct tl_expression *E, struct tl_expression *R) {
  assert (R->type == tlet_polymorphic);
  assert (E->type == tlet_polymorphic_instance);
  struct tl_token *L = tl_token_clone (R->left);
  struct tl_token *x, *y, *z;
  for (x = L->next; x != NULL; x = x->next) {
    for (y = R->right->next, z = E->left->next; y != NULL; y = y->next, z = z->next) {
      if (!strcmp (x->text, y->text)) {
        cstr_free (&x->text);
        x->text = cstr_dup (z->text);
      }
    }
  }
  E->right = E->left;
  E->left = L;
  E->type = tlet_simple;
  E->right_name = cstr_join_with_sugar (E->right);
  E->flag_expanded = 1;
}