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
struct tl_token {char* text; struct tl_token* next; } ;
struct TYPE_2__ {struct tl_token* left; } ;

/* Variables and functions */
 TYPE_1__* expected_expr ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static char *tl_arg_generator (const char *text, int state) {
  //kprintf ("%s: text: %s, state:%d\n", __func__, text, state);
  static int len;
  static struct tl_token *T = NULL;
  if (!state) {
    T = NULL;
    if (expected_expr) {
      T = expected_expr->left;
      if (T) {
        T = T->next;
      }
    }
    len = strlen (text);
  }
  while (T != NULL) {
    char *name = T->text;
    T = T->next;
    if (!strncmp (name, text, len)) {
      return strdup (name);
    }
  }
  return NULL;
}