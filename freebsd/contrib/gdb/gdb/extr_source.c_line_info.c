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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {scalar_t__ line; scalar_t__ pc; TYPE_1__* symtab; } ;
struct TYPE_3__ {int /*<<< orphan*/  filename; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ annotation_level ; 
 TYPE_1__* current_source_symtab ; 
 struct symtabs_and_lines decode_line_spec_1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 scalar_t__ find_line_pc_range (struct symtab_and_line,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  identify_source_line (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 scalar_t__ last_line_listed ; 
 int /*<<< orphan*/  print_address (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  set_next_address (scalar_t__) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 
 int /*<<< orphan*/  xfree (struct symtab_and_line*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
line_info (char *arg, int from_tty)
{
  struct symtabs_and_lines sals;
  struct symtab_and_line sal;
  CORE_ADDR start_pc, end_pc;
  int i;

  init_sal (&sal);		/* initialize to zeroes */

  if (arg == 0)
    {
      sal.symtab = current_source_symtab;
      sal.line = last_line_listed;
      sals.nelts = 1;
      sals.sals = (struct symtab_and_line *)
	xmalloc (sizeof (struct symtab_and_line));
      sals.sals[0] = sal;
    }
  else
    {
      sals = decode_line_spec_1 (arg, 0);

      dont_repeat ();
    }

  /* C++  More than one line may have been specified, as when the user
     specifies an overloaded function name. Print info on them all. */
  for (i = 0; i < sals.nelts; i++)
    {
      sal = sals.sals[i];

      if (sal.symtab == 0)
	{
	  printf_filtered ("No line number information available");
	  if (sal.pc != 0)
	    {
	      /* This is useful for "info line *0x7f34".  If we can't tell the
	         user about a source line, at least let them have the symbolic
	         address.  */
	      printf_filtered (" for address ");
	      wrap_here ("  ");
	      print_address (sal.pc, gdb_stdout);
	    }
	  else
	    printf_filtered (".");
	  printf_filtered ("\n");
	}
      else if (sal.line > 0
	       && find_line_pc_range (sal, &start_pc, &end_pc))
	{
	  if (start_pc == end_pc)
	    {
	      printf_filtered ("Line %d of \"%s\"",
			       sal.line, sal.symtab->filename);
	      wrap_here ("  ");
	      printf_filtered (" is at address ");
	      print_address (start_pc, gdb_stdout);
	      wrap_here ("  ");
	      printf_filtered (" but contains no code.\n");
	    }
	  else
	    {
	      printf_filtered ("Line %d of \"%s\"",
			       sal.line, sal.symtab->filename);
	      wrap_here ("  ");
	      printf_filtered (" starts at address ");
	      print_address (start_pc, gdb_stdout);
	      wrap_here ("  ");
	      printf_filtered (" and ends at ");
	      print_address (end_pc, gdb_stdout);
	      printf_filtered (".\n");
	    }

	  /* x/i should display this line's code.  */
	  set_next_address (start_pc);

	  /* Repeating "info line" should do the following line.  */
	  last_line_listed = sal.line + 1;

	  /* If this is the only line, show the source code.  If it could
	     not find the file, don't do anything special.  */
	  if (annotation_level && sals.nelts == 1)
	    identify_source_line (sal.symtab, sal.line, 0, start_pc);
	}
      else
	/* Is there any case in which we get here, and have an address
	   which the user would want to see?  If we have debugging symbols
	   and no line numbers?  */
	printf_filtered ("Line number %d is out of range for \"%s\".\n",
			 sal.line, sal.symtab->filename);
    }
  xfree (sals.sals);
}