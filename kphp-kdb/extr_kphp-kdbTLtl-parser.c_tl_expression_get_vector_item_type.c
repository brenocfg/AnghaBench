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
struct tl_token {char* text; struct tl_token* next; } ;
struct tl_expression {struct tl_token* right; } ;

/* Variables and functions */

char *tl_expression_get_vector_item_type (struct tl_expression *E) {
  if (E->right == NULL) {
    return NULL;
  }
  struct tl_token *T = E->right;
  if (T == NULL) {
    return NULL;
  }
  T = T->next;
  if (T->next != NULL) {
    return NULL;
  }
  return T->text;
}