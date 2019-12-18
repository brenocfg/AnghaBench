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
struct unwind_state {unsigned long* bp; } ;

/* Variables and functions */
 unsigned long* last_aligned_frame (struct unwind_state*) ; 
 unsigned long* last_frame (struct unwind_state*) ; 

__attribute__((used)) static bool is_last_aligned_frame(struct unwind_state *state)
{
	unsigned long *last_bp = last_frame(state);
	unsigned long *aligned_bp = last_aligned_frame(state);

	/*
	 * GCC can occasionally decide to realign the stack pointer and change
	 * the offset of the stack frame in the prologue of a function called
	 * by head/entry code.  Examples:
	 *
	 * <start_secondary>:
	 *      push   %edi
	 *      lea    0x8(%esp),%edi
	 *      and    $0xfffffff8,%esp
	 *      pushl  -0x4(%edi)
	 *      push   %ebp
	 *      mov    %esp,%ebp
	 *
	 * <x86_64_start_kernel>:
	 *      lea    0x8(%rsp),%r10
	 *      and    $0xfffffffffffffff0,%rsp
	 *      pushq  -0x8(%r10)
	 *      push   %rbp
	 *      mov    %rsp,%rbp
	 *
	 * After aligning the stack, it pushes a duplicate copy of the return
	 * address before pushing the frame pointer.
	 */
	return (state->bp == aligned_bp && *(aligned_bp + 1) == *(last_bp + 1));
}