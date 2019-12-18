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
struct task_struct {int dummy; } ;

/* Variables and functions */
 unsigned char EXR_TRACE ; 
 int /*<<< orphan*/  PT_EXR ; 
 unsigned char h8300_get_reg (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h8300_put_reg (struct task_struct*,int /*<<< orphan*/ ,unsigned char) ; 

void user_enable_single_step(struct task_struct *child)
{
	unsigned char exr;

	exr = h8300_get_reg(child, PT_EXR);
	exr |= EXR_TRACE;
	h8300_put_reg(child, PT_EXR, exr);
}