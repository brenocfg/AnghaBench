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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 int c_val_print (struct type*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 
 int /*<<< orphan*/  extract_signed_integer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (struct ui_file*) ; 
 scalar_t__ is_scmvalue_type (struct type*) ; 
 scalar_t__ scm_inferior_print (int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 
 int /*<<< orphan*/  scm_scmval_print (int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 

int
scm_val_print (struct type *type, char *valaddr, int embedded_offset,
	       CORE_ADDR address, struct ui_file *stream, int format,
	       int deref_ref, int recurse, enum val_prettyprint pretty)
{
  if (is_scmvalue_type (type))
    {
      LONGEST svalue = extract_signed_integer (valaddr, TYPE_LENGTH (type));
      if (scm_inferior_print (svalue, stream, format,
			      deref_ref, recurse, pretty) >= 0)
	{
	}
      else
	{
	  scm_scmval_print (svalue, stream, format,
			    deref_ref, recurse, pretty);
	}

      gdb_flush (stream);
      return (0);
    }
  else
    {
      return c_val_print (type, valaddr, 0, address, stream, format,
			  deref_ref, recurse, pretty);
    }
}