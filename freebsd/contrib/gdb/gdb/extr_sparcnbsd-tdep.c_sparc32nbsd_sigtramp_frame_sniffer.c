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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  find_pc_partial_function (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 scalar_t__ sparc32nbsd_pc_in_sigtramp (int /*<<< orphan*/ ,char*) ; 
 struct frame_unwind const sparc32nbsd_sigcontext_frame_unwind ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static const struct frame_unwind *
sparc32nbsd_sigtramp_frame_sniffer (struct frame_info *next_frame)
{
  CORE_ADDR pc = frame_pc_unwind (next_frame);
  char *name;

  find_pc_partial_function (pc, &name, NULL, NULL);
  if (sparc32nbsd_pc_in_sigtramp (pc, name))
    {
      if (name == NULL || strncmp (name, "__sigtramp_sigcontext", 21))
	return &sparc32nbsd_sigcontext_frame_unwind;
    }

  return NULL;
}