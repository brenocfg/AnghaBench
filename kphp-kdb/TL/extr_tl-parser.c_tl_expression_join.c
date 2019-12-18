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
struct tl_expression {struct tl_token* right; int /*<<< orphan*/  magic; struct tl_token* left; } ;
struct tl_compiler {int dummy; } ;
struct tl_buffer {int /*<<< orphan*/  buff; scalar_t__ pos; } ;

/* Variables and functions */
 char* cstr_dup (int /*<<< orphan*/ ) ; 
 int tl_expression_remove_sugar (struct tl_compiler*,struct tl_expression*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_string_buffer_append_char (struct tl_buffer*,char) ; 
 int /*<<< orphan*/  tl_string_buffer_append_cstr (struct tl_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_string_buffer_free (struct tl_buffer*) ; 
 int /*<<< orphan*/  tl_string_buffer_init (struct tl_buffer*) ; 
 int /*<<< orphan*/  tl_string_buffer_printf (struct tl_buffer*,char*,int /*<<< orphan*/ ) ; 

char *tl_expression_join (struct tl_compiler *C, struct tl_expression *E, int output_magic) {
  struct tl_token *T;
  struct tl_buffer b;
  tl_string_buffer_init (&b);
  for (T = E->left; T != NULL; T = T->next) {
    if (b.pos) {
      tl_string_buffer_append_char (&b, ' ');
    }
    tl_string_buffer_append_cstr (&b, T->text);
    if (output_magic && T == E->left) {
      tl_string_buffer_printf (&b, "#%x", E->magic);
    }
  }
  if (E->right) {
    tl_string_buffer_append_char (&b, ' ');
    tl_string_buffer_append_char (&b, '=');
    for (T = E->right; T != NULL; T = T->next) {
      tl_string_buffer_append_char (&b, ' ');
      tl_string_buffer_append_cstr (&b, T->text);
    }
  }
  tl_string_buffer_append_char (&b, 0);
  int r = tl_expression_remove_sugar (C, E, b.buff);
  if (r < 0) {
    tl_string_buffer_free (&b);
    return NULL;
  }
  char *res = cstr_dup (b.buff);
  tl_string_buffer_free (&b);
  return res;
}