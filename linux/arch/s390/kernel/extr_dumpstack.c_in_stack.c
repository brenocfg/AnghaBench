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
struct stack_info {int type; unsigned long begin; unsigned long end; } ;
typedef  enum stack_type { ____Placeholder_stack_type } stack_type ;

/* Variables and functions */

__attribute__((used)) static inline bool in_stack(unsigned long sp, struct stack_info *info,
			    enum stack_type type, unsigned long low,
			    unsigned long high)
{
	if (sp < low || sp >= high)
		return false;
	info->type = type;
	info->begin = low;
	info->end = high;
	return true;
}