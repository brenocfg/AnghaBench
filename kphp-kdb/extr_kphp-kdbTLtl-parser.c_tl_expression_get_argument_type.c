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
struct tl_expression {struct tl_token* left; } ;

/* Variables and functions */
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

char *tl_expression_get_argument_type (struct tl_expression *E, char *arg_name) {
  if (E == NULL || arg_name == NULL) {
    return NULL;
  }
  struct tl_token *T = E->left;
  if (T == NULL) {
    return NULL;
  }
  int l = strlen (arg_name);
  T = T->next;
  while (T != NULL) {
    if (!strncmp (T->text, arg_name, l) && T->text[l] == ':') {
      return T->text + (l + 1);
    }
    T = T->next;
  }
  return NULL;
}