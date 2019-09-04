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
struct tl_expression {int section; struct tl_expression* next; struct tl_expression* prev; } ;
struct tl_compiler {struct tl_expression* expr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_expression_free (struct tl_expression*) ; 

__attribute__((used)) static void tl_list_expressions_free (struct tl_compiler *C, int section) {
  assert (section >= 0 && section < 2);
  struct tl_expression *L = &C->expr[section], *E, *T;
  for (E = L->next; E != L; E = T) {
    assert (E->section == section);
    T = E->next;
    tl_expression_free (E);
  }
  L->prev = L->next = L;
}