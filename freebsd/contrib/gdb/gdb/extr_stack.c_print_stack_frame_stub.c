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
struct print_stack_frame_args {int /*<<< orphan*/  args; int /*<<< orphan*/  source; int /*<<< orphan*/  level; int /*<<< orphan*/  fi; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_frame_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_stack_frame_stub (void *args)
{
  struct print_stack_frame_args *p = (struct print_stack_frame_args *) args;

  print_frame_info (p->fi, p->level, p->source, p->args);
  return 0;
}