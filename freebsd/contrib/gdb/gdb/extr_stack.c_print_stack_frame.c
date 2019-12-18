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
struct print_stack_frame_args {int level; int source; int args; struct frame_info* fi; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_stack_frame_stub ; 

void
print_stack_frame (struct frame_info *fi, int level, int source)
{
  struct print_stack_frame_args args;

  args.fi = fi;
  args.level = level;
  args.source = source;
  args.args = 1;

  catch_errors (print_stack_frame_stub, (char *) &args, "", RETURN_MASK_ALL);
}