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
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct frame_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_CALL_DUMMY_HAS_COMPLETED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DUMMY_FRAME ; 
 scalar_t__ RETURN_VALUE_REGISTER_CONVENTION ; 
 int /*<<< orphan*/  STORE_RETURN_VALUE (struct type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 scalar_t__ TYPE_CODE_VOID ; 
 struct type* TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VALUE_CONTENTS (struct value*) ; 
 scalar_t__ VALUE_LAZY (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* builtin_type_int ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/ * current_regcache ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  frame_command (char*,int) ; 
 int /*<<< orphan*/  frame_id_eq (struct frame_id,struct frame_id) ; 
 scalar_t__ frame_id_inner (struct frame_id,struct frame_id) ; 
 int /*<<< orphan*/  frame_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 scalar_t__ gdbarch_return_value (int /*<<< orphan*/ ,struct type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbarch_return_value_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  get_frame_base (int /*<<< orphan*/ ) ; 
 struct symbol* get_frame_function (int /*<<< orphan*/ ) ; 
 struct frame_id get_frame_id (int /*<<< orphan*/ ) ; 
 scalar_t__ get_frame_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_selected_frame () ; 
 struct value* parse_and_eval (char*) ; 
 int query (char*,char const*,...) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  read_sp () ; 
 int /*<<< orphan*/  select_frame_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_registers ; 
 scalar_t__ using_struct_return (struct type*,int /*<<< orphan*/ ) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 int /*<<< orphan*/  value_fetch_lazy (struct value*) ; 

void
return_command (char *retval_exp, int from_tty)
{
  struct symbol *thisfun;
  struct value *return_value = NULL;
  const char *query_prefix = "";

  /* FIXME: cagney/2003-10-20: Perform a minimal existance test on the
     target.  If that fails, error out.  For the moment don't rely on
     get_selected_frame as it's error message is the the singularly
     obscure "No registers".  */
  if (!target_has_registers)
    error ("No selected frame.");
  thisfun = get_frame_function (get_selected_frame ());

  /* Compute the return value.  If the computation triggers an error,
     let it bail.  If the return type can't be handled, set
     RETURN_VALUE to NULL, and QUERY_PREFIX to an informational
     message.  */
  if (retval_exp)
    {
      struct type *return_type = NULL;

      /* Compute the return value.  Should the computation fail, this
         call throws an error.  */
      return_value = parse_and_eval (retval_exp);

      /* Cast return value to the return type of the function.  Should
         the cast fail, this call throws an error.  */
      if (thisfun != NULL)
	return_type = TYPE_TARGET_TYPE (SYMBOL_TYPE (thisfun));
      if (return_type == NULL)
	return_type = builtin_type_int;
      return_value = value_cast (return_type, return_value);

      /* Make sure the value is fully evaluated.  It may live in the
         stack frame we're about to pop.  */
      if (VALUE_LAZY (return_value))
	value_fetch_lazy (return_value);

      if (TYPE_CODE (return_type) == TYPE_CODE_VOID)
	/* If the return-type is "void", don't try to find the
           return-value's location.  However, do still evaluate the
           return expression so that, even when the expression result
           is discarded, side effects such as "return i++" still
           occure.  */
	return_value = NULL;
      /* FIXME: cagney/2004-01-17: If the architecture implements both
         return_value and extract_returned_value_address, should allow
         "return" to work - don't set return_value to NULL.  */
      else if (!gdbarch_return_value_p (current_gdbarch)
	       && (TYPE_CODE (return_type) == TYPE_CODE_STRUCT
		   || TYPE_CODE (return_type) == TYPE_CODE_UNION))
	{
	  /* NOTE: cagney/2003-10-20: Compatibility hack for legacy
	     code.  Old architectures don't expect STORE_RETURN_VALUE
	     to be called with with a small struct that needs to be
	     stored in registers.  Don't start doing it now.  */
	  query_prefix = "\
A structure or union return type is not supported by this architecture.\n\
If you continue, the return value that you specified will be ignored.\n";
	  return_value = NULL;
	}
      else if (using_struct_return (return_type, 0))
	{
	  query_prefix = "\
The location at which to store the function's return value is unknown.\n\
If you continue, the return value that you specified will be ignored.\n";
	  return_value = NULL;
	}
    }

  /* Does an interactive user really want to do this?  Include
     information, such as how well GDB can handle the return value, in
     the query message.  */
  if (from_tty)
    {
      int confirmed;
      if (thisfun == NULL)
	confirmed = query ("%sMake selected stack frame return now? ",
			   query_prefix);
      else
	confirmed = query ("%sMake %s return now? ", query_prefix,
			   SYMBOL_PRINT_NAME (thisfun));
      if (!confirmed)
	error ("Not confirmed");
    }

  /* NOTE: cagney/2003-01-18: Is this silly?  Rather than pop each
     frame in turn, should this code just go straight to the relevant
     frame and pop that?  */

  /* First discard all frames inner-to the selected frame (making the
     selected frame current).  */
  {
    struct frame_id selected_id = get_frame_id (get_selected_frame ());
    while (!frame_id_eq (selected_id, get_frame_id (get_current_frame ())))
      {
	if (frame_id_inner (selected_id, get_frame_id (get_current_frame ())))
	  /* Caught in the safety net, oops!  We've gone way past the
             selected frame.  */
	  error ("Problem while popping stack frames (corrupt stack?)");
	frame_pop (get_current_frame ());
      }
  }

  /* Second discard the selected frame (which is now also the current
     frame).  */
  frame_pop (get_current_frame ());

  /* Store RETURN_VAUE in the just-returned register set.  */
  if (return_value != NULL)
    {
      struct type *return_type = VALUE_TYPE (return_value);
      if (!gdbarch_return_value_p (current_gdbarch))
	{
	  STORE_RETURN_VALUE (return_type, current_regcache,
			      VALUE_CONTENTS (return_value));
	}
      /* FIXME: cagney/2004-01-17: If extract_returned_value_address
         is available and the function is using
         RETURN_VALUE_STRUCT_CONVENTION, should use it to find the
         address of the returned value so that it can be assigned.  */
      else
	{
	  gdb_assert (gdbarch_return_value (current_gdbarch, return_type,
					    NULL, NULL, NULL)
		      == RETURN_VALUE_REGISTER_CONVENTION);
	  gdbarch_return_value (current_gdbarch, return_type,
				current_regcache, NULL /*read*/,
				VALUE_CONTENTS (return_value) /*write*/);
	}
    }

  /* If we are at the end of a call dummy now, pop the dummy frame
     too.  */
  /* NOTE: cagney/2003-01-18: Is this silly?  Instead of popping all
     the frames in sequence, should this code just pop the dummy frame
     directly?  */
#ifdef DEPRECATED_CALL_DUMMY_HAS_COMPLETED
  /* Since all up-to-date architectures return direct to the dummy
     breakpoint address, a dummy frame has, by definition, always
     completed.  Hence this method is no longer needed.  */
  if (DEPRECATED_CALL_DUMMY_HAS_COMPLETED (read_pc(), read_sp (),
					   get_frame_base (get_current_frame ())))
    frame_pop (get_current_frame ());
#else
  if (get_frame_type (get_current_frame ()) == DUMMY_FRAME)
    frame_pop (get_current_frame ());
#endif

  /* If interactive, print the frame that is now current.  */
  if (from_tty)
    frame_command ("0", 1);
  else
    select_frame_command ("0", 0);
}