#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_5__ {int /*<<< orphan*/  exc; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_obj_as_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
p(mrb_state *mrb, mrb_value obj, int prompt)
{
  mrb_value val;
  char* msg;

  val = mrb_funcall(mrb, obj, "inspect", 0);
  if (prompt) {
    if (!mrb->exc) {
      fputs(" => ", stdout);
    }
    else {
      val = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
    }
  }
  if (!mrb_string_p(val)) {
    val = mrb_obj_as_string(mrb, obj);
  }
  msg = mrb_locale_from_utf8(RSTRING_PTR(val), (int)RSTRING_LEN(val));
  fwrite(msg, strlen(msg), 1, stdout);
  mrb_locale_free(msg);
  putc('\n', stdout);
}