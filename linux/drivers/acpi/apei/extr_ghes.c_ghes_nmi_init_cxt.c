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
 int /*<<< orphan*/  ghes_proc_in_irq ; 
 int /*<<< orphan*/  ghes_proc_irq_work ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ghes_nmi_init_cxt(void)
{
	init_irq_work(&ghes_proc_irq_work, ghes_proc_in_irq);
}