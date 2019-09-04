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
struct tree {scalar_t__ type; int nc; int /*<<< orphan*/ * c; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_TRY_PES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_parse_declaration (int /*<<< orphan*/ ,int) ; 
 scalar_t__ type_fun_declarations ; 

int tl_parse_fun_declarations (struct tree *T) {
  assert (T->type == type_fun_declarations);
  int i;
  for (i = 0; i < T->nc; i++) {
    TL_TRY_PES (tl_parse_declaration (T->c[i], 1));
  }
  return 1;
}