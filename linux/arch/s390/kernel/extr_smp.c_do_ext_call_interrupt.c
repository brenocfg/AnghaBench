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
struct ext_code {int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQEXT_EMS ; 
 int /*<<< orphan*/  IRQEXT_EXC ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_handle_ext_call () ; 

__attribute__((used)) static void do_ext_call_interrupt(struct ext_code ext_code,
				  unsigned int param32, unsigned long param64)
{
	inc_irq_stat(ext_code.code == 0x1202 ? IRQEXT_EXC : IRQEXT_EMS);
	smp_handle_ext_call();
}