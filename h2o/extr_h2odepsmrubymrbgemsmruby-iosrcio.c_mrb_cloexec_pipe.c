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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_fd_cloexec (int /*<<< orphan*/ *,int) ; 
 int pipe (int*) ; 

__attribute__((used)) static int
mrb_cloexec_pipe(mrb_state *mrb, int fildes[2])
{
  int ret;
  ret = pipe(fildes);
  if (ret == -1)
    return -1;
  mrb_fd_cloexec(mrb, fildes[0]);
  mrb_fd_cloexec(mrb, fildes[1]);
  return ret;
}