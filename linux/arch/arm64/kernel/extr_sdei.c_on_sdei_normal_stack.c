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
struct stack_info {unsigned long low; unsigned long high; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned long SDEI_STACK_SIZE ; 
 int /*<<< orphan*/  STACK_TYPE_SDEI_NORMAL ; 
 scalar_t__ raw_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_stack_normal_ptr ; 

__attribute__((used)) static bool on_sdei_normal_stack(unsigned long sp, struct stack_info *info)
{
	unsigned long low = (unsigned long)raw_cpu_read(sdei_stack_normal_ptr);
	unsigned long high = low + SDEI_STACK_SIZE;

	if (!low)
		return false;

	if (sp < low || sp >= high)
		return false;

	if (info) {
		info->low = low;
		info->high = high;
		info->type = STACK_TYPE_SDEI_NORMAL;
	}

	return true;
}