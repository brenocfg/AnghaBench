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
struct varobj {scalar_t__ format; int /*<<< orphan*/ * value; int /*<<< orphan*/  num_children; } ;
struct ui_file {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int TYPE_CODE (int /*<<< orphan*/ ) ; 
#define  TYPE_CODE_ARRAY 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 int /*<<< orphan*/  VALUE_LAZY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_val_print (int /*<<< orphan*/ *,struct ui_file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/ * format_code ; 
 int /*<<< orphan*/  gdb_value_fetch_lazy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_type (struct varobj*) ; 
 struct cleanup* make_cleanup_ui_file_delete (struct ui_file*) ; 
 struct ui_file* mem_fileopen () ; 
 char* ui_file_xstrdup (struct ui_file*,long*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
c_value_of_variable (struct varobj *var)
{
  /* BOGUS: if val_print sees a struct/class, it will print out its
     children instead of "{...}" */

  switch (TYPE_CODE (get_type (var)))
    {
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      return xstrdup ("{...}");
      /* break; */

    case TYPE_CODE_ARRAY:
      {
	char *number;
	xasprintf (&number, "[%d]", var->num_children);
	return (number);
      }
      /* break; */

    default:
      {
	if (var->value == NULL)
	  {
	    /* This can happen if we attempt to get the value of a struct
	       member when the parent is an invalid pointer. This is an
	       error condition, so we should tell the caller. */
	    return NULL;
	  }
	else
	  {
	    long dummy;
	    struct ui_file *stb = mem_fileopen ();
	    struct cleanup *old_chain = make_cleanup_ui_file_delete (stb);
	    char *thevalue;

	    if (VALUE_LAZY (var->value))
	      gdb_value_fetch_lazy (var->value);
	    common_val_print (var->value, stb,
			      format_code[(int) var->format], 1, 0, 0);
	    thevalue = ui_file_xstrdup (stb, &dummy);
	    do_cleanups (old_chain);
	return thevalue;
      }
      }
    }
}