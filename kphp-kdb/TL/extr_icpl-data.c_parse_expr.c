#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; size_t start; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ icpl_token_t ;
typedef  int /*<<< orphan*/  icpl_cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cell_new_any () ; 
 int /*<<< orphan*/ * cell_new_combinator (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cell_new_nat (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cell_new_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cell_new_variable (char const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int icpl_failf (char const*,size_t,char*) ; 
#define  lt_any 133 
#define  lt_cbrace 132 
#define  lt_combinator 131 
#define  lt_nat 130 
#define  lt_obrace 129 
#define  lt_variable 128 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int parse_expr (const char *input, icpl_token_t *a, int tokens, icpl_cell_t **R) {
  int i, j, s;
  icpl_cell_t *c, *r = NULL;
  *R = NULL;
  for (i = 0; i < tokens; i++) {
     switch (a[i].type) {
       case lt_obrace:
         s = 1;
         for (j = i + 1; s > 0 && j < tokens; j++) {
           switch (a[j].type) {
             case lt_obrace: s++; break;
             case lt_cbrace: s--; break;
             default: break;
           }
         }
         if (s > 0) {
           return icpl_failf (input, a[i].start, "closing bracket wasn't found");
         }
         //a[i]   : '('
         //a[j-1] : ')'
         if (parse_expr (input, a + (i + 1), j - (i + 2), &c) < 0) {
           return -1;
         }
         r = cell_new_node (r, c);
         i = j;
       break;
       case lt_cbrace: return icpl_failf (input, a[i].start, "unexpected closing bracket");
       case lt_combinator: r = cell_new_node (r, cell_new_combinator (input + a[i].start, a[i].length)); break;
       case lt_nat: r = cell_new_node (r, cell_new_nat (input + a[i].start, a[i].length)); break;
       case lt_variable: r = cell_new_node (r, cell_new_variable (input[a[i].start])); break;
       case lt_any: r = cell_new_node (r, cell_new_any ()); break;
       default: fprintf (stderr, "Unexpected lt (%d) at pos %d\n", a[i].type, i); assert (0);
     }
  }
  *R = r;
  return 0;
}