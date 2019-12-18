#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct symtab {int dummy; } ;
struct linetable {TYPE_1__* item; } ;
struct TYPE_2__ {int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct linetable* LINETABLE (struct symtab*) ; 
 struct symtab* find_line_symtab (struct symtab*,int,int*,int /*<<< orphan*/ *) ; 

int
find_line_pc (struct symtab *symtab, int line, CORE_ADDR *pc)
{
  struct linetable *l;
  int ind;

  *pc = 0;
  if (symtab == 0)
    return 0;

  symtab = find_line_symtab (symtab, line, &ind, NULL);
  if (symtab != NULL)
    {
      l = LINETABLE (symtab);
      *pc = l->item[ind].pc;
      return 1;
    }
  else
    return 0;
}