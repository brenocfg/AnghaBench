#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct type {scalar_t__ modifiable; } ;
typedef  struct type* VALUE_TYPE ;
struct TYPE_5__ {TYPE_1__* symtab; scalar_t__ line; scalar_t__ pc; } ;
struct TYPE_4__ {int /*<<< orphan*/ * filename; } ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/ * DEPRECATED_SYMBOL_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct type*) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  builtin_type_char ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* create_array_type (struct type*,int /*<<< orphan*/ ,struct type*) ; 
 struct type* create_range_type (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * find_pc_function (int) ; 
 TYPE_2__ find_pc_line (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_internalvar (char*) ; 
 struct type* lookup_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_internalvar (int /*<<< orphan*/ ,struct type*) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * traceframe_fun ; 
 TYPE_2__ traceframe_sal ; 
 struct type* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* value_from_pointer (struct type*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_traceframe_context (CORE_ADDR trace_pc)
{
  static struct type *func_string, *file_string;
  static struct type *func_range, *file_range;
  struct value *func_val;
  struct value *file_val;
  static struct type *charstar;
  int len;

  if (charstar == (struct type *) NULL)
    charstar = lookup_pointer_type (builtin_type_char);

  if (trace_pc == -1)		/* cease debugging any trace buffers */
    {
      traceframe_fun = 0;
      traceframe_sal.pc = traceframe_sal.line = 0;
      traceframe_sal.symtab = NULL;
      set_internalvar (lookup_internalvar ("trace_func"),
		       value_from_pointer (charstar, (LONGEST) 0));
      set_internalvar (lookup_internalvar ("trace_file"),
		       value_from_pointer (charstar, (LONGEST) 0));
      set_internalvar (lookup_internalvar ("trace_line"),
		       value_from_longest (builtin_type_int, (LONGEST) - 1));
      return;
    }

  /* save as globals for internal use */
  traceframe_sal = find_pc_line (trace_pc, 0);
  traceframe_fun = find_pc_function (trace_pc);

  /* save linenumber as "$trace_line", a debugger variable visible to users */
  set_internalvar (lookup_internalvar ("trace_line"),
		   value_from_longest (builtin_type_int,
				       (LONGEST) traceframe_sal.line));

  /* save func name as "$trace_func", a debugger variable visible to users */
  if (traceframe_fun == NULL ||
      DEPRECATED_SYMBOL_NAME (traceframe_fun) == NULL)
    set_internalvar (lookup_internalvar ("trace_func"),
		     value_from_pointer (charstar, (LONGEST) 0));
  else
    {
      len = strlen (DEPRECATED_SYMBOL_NAME (traceframe_fun));
      func_range = create_range_type (func_range,
				      builtin_type_int, 0, len - 1);
      func_string = create_array_type (func_string,
				       builtin_type_char, func_range);
      func_val = allocate_value (func_string);
      VALUE_TYPE (func_val) = func_string;
      memcpy (VALUE_CONTENTS_RAW (func_val),
	      DEPRECATED_SYMBOL_NAME (traceframe_fun),
	      len);
      func_val->modifiable = 0;
      set_internalvar (lookup_internalvar ("trace_func"), func_val);
    }

  /* save file name as "$trace_file", a debugger variable visible to users */
  if (traceframe_sal.symtab == NULL ||
      traceframe_sal.symtab->filename == NULL)
    set_internalvar (lookup_internalvar ("trace_file"),
		     value_from_pointer (charstar, (LONGEST) 0));
  else
    {
      len = strlen (traceframe_sal.symtab->filename);
      file_range = create_range_type (file_range,
				      builtin_type_int, 0, len - 1);
      file_string = create_array_type (file_string,
				       builtin_type_char, file_range);
      file_val = allocate_value (file_string);
      VALUE_TYPE (file_val) = file_string;
      memcpy (VALUE_CONTENTS_RAW (file_val),
	      traceframe_sal.symtab->filename,
	      len);
      file_val->modifiable = 0;
      set_internalvar (lookup_internalvar ("trace_file"), file_val);
    }
}