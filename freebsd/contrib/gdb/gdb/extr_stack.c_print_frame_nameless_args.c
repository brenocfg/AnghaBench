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
struct ui_file {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 scalar_t__ get_frame_args_address (struct frame_info*) ; 
 long read_memory_integer (scalar_t__,int) ; 

__attribute__((used)) static void
print_frame_nameless_args (struct frame_info *fi, long start, int num,
			   int first, struct ui_file *stream)
{
  int i;
  CORE_ADDR argsaddr;
  long arg_value;

  for (i = 0; i < num; i++)
    {
      QUIT;
      argsaddr = get_frame_args_address (fi);
      if (!argsaddr)
	return;
      arg_value = read_memory_integer (argsaddr + start, sizeof (int));
      if (!first)
	fprintf_filtered (stream, ", ");
      fprintf_filtered (stream, "%ld", arg_value);
      first = 0;
      start += sizeof (int);
    }
}