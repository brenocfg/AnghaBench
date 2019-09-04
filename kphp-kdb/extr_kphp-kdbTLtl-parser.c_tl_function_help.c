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
struct tl_expression {scalar_t__ flag_visited; struct tl_expression* next; } ;
struct tl_compiler {struct tl_expression* expr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TL_SECTION_FUNCTIONS ; 
 size_t TL_SECTION_TYPES ; 
 int /*<<< orphan*/  tl_expression_dfs_visit (struct tl_compiler*,struct tl_expression*) ; 
 int /*<<< orphan*/  tl_expression_write_to_file (int /*<<< orphan*/ *,struct tl_compiler*,struct tl_expression*) ; 
 struct tl_expression* tl_list_expressions_find_by_combinator_name (struct tl_compiler*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int tl_function_help (struct tl_compiler *C, char *rpc_function_name, FILE *f) {
  struct tl_expression *F = tl_list_expressions_find_by_combinator_name (C, TL_SECTION_FUNCTIONS, rpc_function_name, NULL);
  if (F == NULL) {
    return -1;
  }
  tl_expression_dfs_visit (C, F);
  F->flag_visited = 0;
  struct tl_expression *E;
  for (E = C->expr[TL_SECTION_TYPES].next; E != &C->expr[TL_SECTION_TYPES]; E = E->next) {
    if (E->flag_visited) {
      tl_expression_write_to_file (f, C, E);
      E->flag_visited = 0;
    }
  }
  tl_expression_write_to_file (f, C, F);
  return 0;
}