#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_11__ {scalar_t__ jmp; scalar_t__ exc; } ;
typedef  TYPE_1__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  jmp_buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  E_LOAD_ERROR ; 
 int MAX_PATH ; 
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int compile_rb2mrb (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eval_load_irep (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raisef (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mrb_read_irep_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (TYPE_1__*,char*) ; 
 char* mrb_str_to_cstr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int umask (int) ; 

__attribute__((used)) static mrb_value
mrb_require_load_rb_str(mrb_state *mrb, mrb_value self)
{
  char *path_ptr = NULL;
#if defined(_WIN32) || defined(_WIN64)
  char tmpname[MAX_PATH] = "tmp.XXXXXXXX";
#else
  char tmpname[] = "tmp.XXXXXXXX";
#endif
  mode_t mask;
  FILE *tmpfp = NULL;
  int fd = -1, ret;
  mrb_irep *irep;
  mrb_value code, path = mrb_nil_value();

  mrb_get_args(mrb, "S|S", &code, &path);
  if (!mrb_string_p(path)) {
    path = mrb_str_new_cstr(mrb, "-");
  }
  path_ptr = mrb_str_to_cstr(mrb, path);

  mask = umask(077);
  fd = mkstemp(tmpname);
  if (fd == -1) {
    mrb_sys_fail(mrb, "can't create mkstemp() at mrb_require_load_rb_str");
  }
  umask(mask);

  tmpfp = fdopen(fd, "r+");
  if (tmpfp == NULL) {
    close(fd);
    mrb_sys_fail(mrb, "can't open temporay file at mrb_require_load_rb_str");
  }

  ret = compile_rb2mrb(mrb, RSTRING_PTR(code), RSTRING_LEN(code), path_ptr, tmpfp);
  if (ret != MRB_DUMP_OK) {
    fclose(tmpfp);
    remove(tmpname);
    mrb_raisef(mrb, E_LOAD_ERROR, "can't load file -- %S", path);
    return mrb_nil_value();
  }

  rewind(tmpfp);
  irep = mrb_read_irep_file(mrb, tmpfp);
  fclose(tmpfp);
  remove(tmpname);

  if (irep) {
    eval_load_irep(mrb, irep);
  } else if (mrb->exc) {
    // fail to load
    longjmp(*(jmp_buf*)mrb->jmp, 1);
  } else {
    mrb_raisef(mrb, E_LOAD_ERROR, "can't load file -- %S", path);
    return mrb_nil_value();
  }

  return mrb_true_value();
}