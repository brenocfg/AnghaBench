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
struct symbol_search {struct symbol_search* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct symbol_search*) ; 

void
free_search_symbols (struct symbol_search *symbols)
{
  struct symbol_search *p;
  struct symbol_search *next;

  for (p = symbols; p != NULL; p = next)
    {
      next = p->next;
      xfree (p);
    }
}