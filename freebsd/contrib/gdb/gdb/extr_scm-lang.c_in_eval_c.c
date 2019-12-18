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
struct symtab_and_line {TYPE_1__* symtab; } ;
struct TYPE_2__ {char* filename; } ;

/* Variables and functions */
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
in_eval_c (void)
{
  struct symtab_and_line cursal = get_current_source_symtab_and_line ();
  
  if (cursal.symtab && cursal.symtab->filename)
    {
      char *filename = cursal.symtab->filename;
      int len = strlen (filename);
      if (len >= 6 && strcmp (filename + len - 6, "eval.c") == 0)
	return 1;
    }
  return 0;
}