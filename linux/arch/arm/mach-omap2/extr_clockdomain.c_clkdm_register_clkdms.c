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
struct clockdomain {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int /*<<< orphan*/  _clkdm_register (struct clockdomain*) ; 
 int /*<<< orphan*/  arch_clkdm ; 

int clkdm_register_clkdms(struct clockdomain **cs)
{
	struct clockdomain **c = NULL;

	if (!arch_clkdm)
		return -EACCES;

	if (!cs)
		return -EINVAL;

	for (c = cs; *c; c++)
		_clkdm_register(*c);

	return 0;
}