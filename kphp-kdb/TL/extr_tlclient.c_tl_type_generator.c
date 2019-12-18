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
struct tl_expression {struct tl_expression* rnext; TYPE_1__* left; } ;
struct TYPE_2__ {char* text; } ;

/* Variables and functions */
 int /*<<< orphan*/  compiler ; 
 int /*<<< orphan*/  expected_type ; 
 char* strdup (char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 
 struct tl_expression* tl_expression_find_first_by_composite_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *tl_type_generator (const char *text, int state) {
  //kprintf ("%s: text: %s, state:%d\n", __func__, text, state);
  static int len;
  static struct tl_expression *E;
  if (!state) {
    E = tl_expression_find_first_by_composite_typename (&compiler, expected_type);
    len = strlen (text);
  }
  while (E != NULL) {
    char *name = E->left->text;
    E = E->rnext;
    if (!strncmp (name, text, len)) {
      return strdup (name);
    }
  }
  return NULL;
}