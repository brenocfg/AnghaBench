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
struct sym_fns {struct sym_fns* next; } ;

/* Variables and functions */
 struct sym_fns* symtab_fns ; 

void
add_symtab_fns (struct sym_fns *sf)
{
  sf->next = symtab_fns;
  symtab_fns = sf;
}