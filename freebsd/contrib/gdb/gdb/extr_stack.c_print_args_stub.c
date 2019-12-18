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
struct print_args_args {int /*<<< orphan*/  stream; int /*<<< orphan*/  fi; int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int FRAME_NUM_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ FRAME_NUM_ARGS_P () ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  print_frame_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_args_stub (void *args)
{
  int numargs;
  struct print_args_args *p = (struct print_args_args *) args;

  if (FRAME_NUM_ARGS_P ())
    {
      numargs = FRAME_NUM_ARGS (p->fi);
      gdb_assert (numargs >= 0);
    }
  else
    numargs = -1;
  print_frame_args (p->func, p->fi, numargs, p->stream);
  return 0;
}