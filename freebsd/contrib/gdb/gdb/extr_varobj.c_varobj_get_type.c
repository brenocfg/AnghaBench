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
struct varobj {int /*<<< orphan*/  type; } ;
struct value {int dummy; } ;
struct ui_file {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPLUS_FAKE_CHILD (struct varobj*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_ui_file_delete (struct ui_file*) ; 
 struct ui_file* mem_fileopen () ; 
 int /*<<< orphan*/  not_lval ; 
 int /*<<< orphan*/  type_print (int /*<<< orphan*/ ,char*,struct ui_file*,int) ; 
 char* ui_file_xstrdup (struct ui_file*,long*) ; 
 struct value* value_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
varobj_get_type (struct varobj *var)
{
  struct value *val;
  struct cleanup *old_chain;
  struct ui_file *stb;
  char *thetype;
  long length;

  /* For the "fake" variables, do not return a type. (It's type is
     NULL, too.) */
  if (CPLUS_FAKE_CHILD (var))
    return NULL;

  stb = mem_fileopen ();
  old_chain = make_cleanup_ui_file_delete (stb);

  /* To print the type, we simply create a zero ``struct value *'' and
     cast it to our type. We then typeprint this variable. */
  val = value_zero (var->type, not_lval);
  type_print (VALUE_TYPE (val), "", stb, -1);

  thetype = ui_file_xstrdup (stb, &length);
  do_cleanups (old_chain);
  return thetype;
}