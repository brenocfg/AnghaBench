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
struct tl_expression {struct tl_expression* next; } ;
struct tl_compiler {int flag_output_magic; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  tl_expression_write_to_file (int /*<<< orphan*/ *,struct tl_compiler*,struct tl_expression*) ; 

void tl_write_list_expressions_free_to_file (FILE *f, struct tl_compiler *C, struct tl_expression *L) {
  struct tl_expression *E;
  int old_output_magic = C->flag_output_magic;
  C->flag_output_magic = 1;
  for (E = L->next; E != L; E = E->next) {
    tl_expression_write_to_file (f, C, E);
  }
  C->flag_output_magic = old_output_magic;
}