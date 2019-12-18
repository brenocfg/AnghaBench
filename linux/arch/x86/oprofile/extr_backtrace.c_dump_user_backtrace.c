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
struct stack_frame {struct stack_frame* next_frame; int /*<<< orphan*/  return_address; } ;
typedef  int /*<<< orphan*/  bufhead ;

/* Variables and functions */
 unsigned long copy_from_user_nmi (struct stack_frame*,struct stack_frame*,int) ; 
 int /*<<< orphan*/  oprofile_add_trace (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stack_frame *dump_user_backtrace(struct stack_frame *head)
{
	/* Also check accessibility of one struct frame_head beyond: */
	struct stack_frame bufhead[2];
	unsigned long bytes;

	bytes = copy_from_user_nmi(bufhead, head, sizeof(bufhead));
	if (bytes != 0)
		return NULL;

	oprofile_add_trace(bufhead[0].return_address);

	/* frame pointers should strictly progress back up the stack
	 * (towards higher addresses) */
	if (head >= bufhead[0].next_frame)
		return NULL;

	return bufhead[0].next_frame;
}