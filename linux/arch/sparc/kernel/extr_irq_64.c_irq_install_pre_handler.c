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

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*) ; 

void irq_install_pre_handler(int irq,
			     void (*func)(unsigned int, void *, void *),
			     void *arg1, void *arg2)
{
	pr_warn("IRQ pre handler NOT supported.\n");
}