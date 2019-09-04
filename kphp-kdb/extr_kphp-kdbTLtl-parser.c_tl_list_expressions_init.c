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
struct tl_expression {struct tl_expression* next; struct tl_expression* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  vkprintf (int,char*,struct tl_expression*) ; 

void tl_list_expressions_init (struct tl_expression *E) {
  vkprintf (4, "tl_list_expressions_init (%p)\n", E);
  E->prev = E->next = E;
}