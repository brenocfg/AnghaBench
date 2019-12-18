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
struct tl_expression {scalar_t__ type; char* text; } ;
struct tl_compiler {int flag_output_magic; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstr_free (char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* tl_expression_join (struct tl_compiler*,struct tl_expression*,int) ; 
 scalar_t__ tlet_simple ; 

void tl_expression_write_to_file (FILE *f, struct tl_compiler *C, struct tl_expression *E) {
  int output_magic = C->flag_output_magic;
  if (E->type != tlet_simple) {
    output_magic = 0;
  }
  char *t = NULL;
  if (output_magic) {
    t = tl_expression_join (C, E, 1);
    assert (t != NULL);
  }
  fprintf (f, "%s;\n", t ? t : E->text);
  if (t != NULL) {
    cstr_free (&t);
  }
}