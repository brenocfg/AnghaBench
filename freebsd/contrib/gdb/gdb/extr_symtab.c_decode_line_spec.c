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
struct symtabs_and_lines {int dummy; } ;
struct symtab_and_line {int /*<<< orphan*/  line; int /*<<< orphan*/  symtab; } ;

/* Variables and functions */
 struct symtabs_and_lines decode_line_1 (char**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 

struct symtabs_and_lines
decode_line_spec (char *string, int funfirstline)
{
  struct symtabs_and_lines sals;
  struct symtab_and_line cursal;
  
  if (string == 0)
    error ("Empty line specification.");
    
  /* We use whatever is set as the current source line. We do not try
     and get a default  or it will recursively call us! */  
  cursal = get_current_source_symtab_and_line ();
  
  sals = decode_line_1 (&string, funfirstline,
			cursal.symtab, cursal.line,
			(char ***) NULL, NULL);

  if (*string)
    error ("Junk at end of line specification: %s", string);
  return sals;
}