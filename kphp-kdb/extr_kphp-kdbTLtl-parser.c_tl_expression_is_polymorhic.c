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
struct tl_token {struct tl_token* next; } ;
struct tl_expression {struct tl_token* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_token_is_type_name (struct tl_token*) ; 
 int /*<<< orphan*/  tl_token_is_variable_type (struct tl_token*) ; 

int tl_expression_is_polymorhic (struct tl_expression *E) {
  struct tl_token *u = E->right;
  if (u == NULL) {
    return 0;
  }
  if (!tl_token_is_type_name (u)) {
    return 0;
  }
  u = u->next;
  if (u == NULL) {
    return 0;
  }
  while (u != NULL) {
    if (!tl_token_is_variable_type (u)) {
      return 0;
    }
    u = u->next;
  }
  return 1;
}