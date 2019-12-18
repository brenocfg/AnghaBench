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
struct value {int dummy; } ;
struct symbol {int dummy; } ;
struct frame_info {int dummy; } ;
struct block {int dummy; } ;

/* Variables and functions */
 struct symbol* BLOCK_FUNCTION (struct block*) ; 
 scalar_t__ SYMBOL_PRINT_NAME (struct symbol*) ; 
 struct frame_info* block_innermost_frame (struct block*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct value* read_var_value (struct symbol*,struct frame_info*) ; 
 scalar_t__ symbol_read_needs_frame (struct symbol*) ; 

struct value *
value_of_variable (struct symbol *var, struct block *b)
{
  struct value *val;
  struct frame_info *frame = NULL;

  if (!b)
    frame = NULL;		/* Use selected frame.  */
  else if (symbol_read_needs_frame (var))
    {
      frame = block_innermost_frame (b);
      if (!frame)
	{
	  if (BLOCK_FUNCTION (b)
	      && SYMBOL_PRINT_NAME (BLOCK_FUNCTION (b)))
	    error ("No frame is currently executing in block %s.",
		   SYMBOL_PRINT_NAME (BLOCK_FUNCTION (b)));
	  else
	    error ("No frame is currently executing in specified block");
	}
    }

  val = read_var_value (var, frame);
  if (!val)
    error ("Address of symbol \"%s\" is unknown.", SYMBOL_PRINT_NAME (var));

  return val;
}