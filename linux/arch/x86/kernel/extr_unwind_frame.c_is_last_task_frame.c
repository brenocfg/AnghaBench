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
struct unwind_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_last_aligned_frame (struct unwind_state*) ; 
 scalar_t__ is_last_frame (struct unwind_state*) ; 
 scalar_t__ is_last_ftrace_frame (struct unwind_state*) ; 

__attribute__((used)) static bool is_last_task_frame(struct unwind_state *state)
{
	return is_last_frame(state) || is_last_aligned_frame(state) ||
	       is_last_ftrace_frame(state);
}