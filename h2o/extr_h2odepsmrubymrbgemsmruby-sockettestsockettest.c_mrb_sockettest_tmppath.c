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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int close (int) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int unlink (char*) ; 

mrb_value
mrb_sockettest_tmppath(mrb_state *mrb, mrb_value klass)
{
  char name[] = "mruby-socket.XXXXXXXX";
  int fd = mkstemp(name);
  if (fd == -1) {
    mrb_sys_fail(mrb, 0);
  }
  if (close(fd) == -1) {
    mrb_sys_fail(mrb, 0);
  }
  if (unlink(name) == -1) {
    mrb_sys_fail(mrb, 0);
  }
  return mrb_str_new_cstr(mrb, name);
}