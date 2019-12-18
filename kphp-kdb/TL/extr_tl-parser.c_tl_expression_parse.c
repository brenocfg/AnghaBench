#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tl_expression {char* text; scalar_t__ type; scalar_t__ section; unsigned int magic; TYPE_1__* right; void* right_name; TYPE_2__* left; struct tl_expression* next; } ;
struct tl_compiler {int /*<<< orphan*/  errors; struct tl_expression* expr; } ;
struct TYPE_5__ {char* text; } ;
struct TYPE_4__ {scalar_t__ next; } ;

/* Variables and functions */
 scalar_t__ TL_SECTION_FUNCTIONS ; 
 size_t TL_SECTION_TYPES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cstr_free (char**) ; 
 void* cstr_join_with_sugar (TYPE_1__*) ; 
 void* cstr_substr (char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 
 char* strchr (char*,char) ; 
 void* tl_expresion_split (struct tl_compiler*,struct tl_expression*,char*,int) ; 
 int /*<<< orphan*/  tl_expression_expand (struct tl_expression*,struct tl_expression*) ; 
 scalar_t__ tl_expression_is_polymorhic (struct tl_expression*) ; 
 int tl_failf (struct tl_compiler*,char*,char*) ; 
 scalar_t__ tl_token_polymorphic_match (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ tlet_polymorphic ; 
 scalar_t__ tlet_polymorphic_instance ; 
 scalar_t__ tlet_simple ; 

int tl_expression_parse (struct tl_compiler *C, struct tl_expression *E) {
  char *p = strchr (E->text, '=');
  if (p == NULL) {
    E->left = tl_expresion_split (C, E, E->text, 1);
    if (E->left == NULL) {
      return -1;
    }
    E->right = NULL;
    E->type = tlet_polymorphic_instance;
    if (E->section) {
      return tl_failf (C, "polymorphic instance in the '---functions---' section, expr: %s", E->text);
    }
    struct tl_expression *A = C->expr[TL_SECTION_TYPES].next;
    while (A != E) {
      assert (A != &C->expr[TL_SECTION_TYPES]);
      if (A->type == tlet_polymorphic && tl_token_polymorphic_match (A->right, E->left)) {
        tl_expression_expand (E, A);
        return 0;
      }
      A = A->next;
    }
    return tl_failf (C, "don't find polymorphic rule, expr: %s", E->text);
  }
  if (p == E->text || p[-1] != ' ' || p[1] != ' ') {
    return tl_failf (C, "'=' should be surrounded by spaces, expr: %s", E->text);
  }
  if (strchr (p + 1, '=') != NULL) {
    return tl_failf (C, "'=' occures multiple times, expr: %s", E->text);
  }

  char *first = cstr_substr (E->text, 0, p - E->text - 1);
  E->left = tl_expresion_split (C, E, first, 0);
  cstr_free (&first);

  if (E->left == NULL) {
    return tl_failf (C, "empty lhs, expr: %s\n", E->text);
  }

  char *q = strchr (E->left->text, '#');
  if (q != NULL) {
    unsigned int magic = 0;
    char ch;
    int r = sscanf (q + 1, "%x%c", &magic, &ch);
    if (r != 1) {
      return tl_failf (C, "can't parse combinator magic number, expr: %s", E->text);
    }
    E->magic = magic;
    char *old = E->left->text;
    E->left->text = cstr_substr (old, 0, q - old);
    cstr_free (&old);
  }
  E->type = tlet_simple;
  E->right = tl_expresion_split (C, E, p + 1, E->section ? 0 : 1);
  if (E->right == NULL) {
    if (!C->errors) {
      return tl_failf (C, "empty rhs, expr: %s\n", E->text);
    }
    return -1;
  }

  if (E->section == TL_SECTION_FUNCTIONS) {
    E->right_name = cstr_join_with_sugar (E->right);
    return 0;
  }

  /* type declaration section */
  if (tl_expression_is_polymorhic (E)) {
    E->type = tlet_polymorphic;
    return 0;
  }

  if (E->right->next) {
    return tl_failf (C, "rhs contains more than one word, but it isn't polymorhic (args should be in ['alpha', 'beta', ...]), expr: %s\n", E->text);
  }

  E->right_name = cstr_join_with_sugar (E->right);

  return 0;
}