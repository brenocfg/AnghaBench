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
struct tl_expression {struct tl_expression* rnext; } ;
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tl_expression_dfs_visit (struct tl_compiler*,struct tl_expression*) ; 
 struct tl_expression* tl_expression_find_first_by_composite_typename (struct tl_compiler*,char*) ; 

__attribute__((used)) static void dfs_typename_visit (struct tl_compiler *C, char *typename) {
  if (typename == NULL) {
    return;
  }
  struct tl_expression *E = tl_expression_find_first_by_composite_typename (C, typename);
  while (E != NULL) {
    tl_expression_dfs_visit (C, E);
    E = E->rnext;
  }
}