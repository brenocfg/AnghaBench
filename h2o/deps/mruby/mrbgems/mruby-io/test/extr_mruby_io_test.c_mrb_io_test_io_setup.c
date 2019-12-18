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
typedef  int /*<<< orphan*/  sun0 ;
struct sockaddr_un {char* sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int symlink (char*,char*) ; 
 int umask (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static mrb_value
mrb_io_test_io_setup(mrb_state *mrb, mrb_value self)
{
  char rfname[]      = "tmp.mruby-io-test-r.XXXXXXXX";
  char wfname[]      = "tmp.mruby-io-test-w.XXXXXXXX";
  char symlinkname[] = "tmp.mruby-io-test-l.XXXXXXXX";
  char socketname[]  = "tmp.mruby-io-test-s.XXXXXXXX";
  char msg[] = "mruby io test\n";
  mode_t mask;
  int fd0, fd1;
  FILE *fp;

#if !defined(_WIN32) && !defined(_WIN64)
  int fd2, fd3;
  struct sockaddr_un sun0;
#endif

  mask = umask(077);
  fd0 = mkstemp(rfname);
  fd1 = mkstemp(wfname);
  if (fd0 == -1 || fd1 == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't create temporary file");
    return mrb_nil_value();
  }
  close(fd0);
  close(fd1);

#if !defined(_WIN32) && !defined(_WIN64)
  fd2 = mkstemp(symlinkname);
  fd3 = mkstemp(socketname);
  if (fd2 == -1 || fd3 == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't create temporary file");
    return mrb_nil_value();
  }
#endif
  umask(mask);

  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$mrbtest_io_rfname"), mrb_str_new_cstr(mrb, rfname));
  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$mrbtest_io_wfname"), mrb_str_new_cstr(mrb, wfname));
  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$mrbtest_io_symlinkname"), mrb_str_new_cstr(mrb, symlinkname));
  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$mrbtest_io_socketname"), mrb_str_new_cstr(mrb, socketname));
  mrb_gv_set(mrb, mrb_intern_cstr(mrb, "$mrbtest_io_msg"), mrb_str_new_cstr(mrb, msg));

  fp = fopen(rfname, "wb");
  if (fp == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't open temporary file");
    return mrb_nil_value();
  }
  fputs(msg, fp);
  fclose(fp);

  fp = fopen(wfname, "wb");
  if (fp == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't open temporary file");
    return mrb_nil_value();
  }
  fclose(fp);

#if !defined(_WIN32) && !defined(_WIN64)
  unlink(symlinkname);
  close(fd2);
  if (symlink(rfname, symlinkname) == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't make a symbolic link");
  }

  unlink(socketname);
  close(fd3);
  fd3 = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd3 == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't make a socket");
  }
  sun0.sun_family = AF_UNIX;
  snprintf(sun0.sun_path, sizeof(sun0.sun_path), "%s", socketname);
  if (bind(fd3, (struct sockaddr *)&sun0, sizeof(sun0)) == -1) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "can't bind AF_UNIX socket to %S: %S",
               mrb_str_new_cstr(mrb, sun0.sun_path),
               mrb_fixnum_value(errno));
  }
  close(fd3);
#endif

  return mrb_true_value();
}