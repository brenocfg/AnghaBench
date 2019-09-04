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
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  mrb_io_test_io_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int symlink (char*,char*) ; 

__attribute__((used)) static mrb_value
mrb_io_test_file_setup(mrb_state *mrb, mrb_value self)
{
  mrb_value ary = mrb_io_test_io_setup(mrb, self);
#if !defined(_WIN32) && !defined(_WIN64)
  if (symlink("/usr/bin", "test-bin") == -1) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "can't make a symbolic link");
  }
#endif

  return ary;
}