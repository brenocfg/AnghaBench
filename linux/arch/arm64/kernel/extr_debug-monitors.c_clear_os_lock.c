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
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  osdlr_el1 ; 
 int /*<<< orphan*/  oslar_el1 ; 
 int /*<<< orphan*/  write_sysreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clear_os_lock(unsigned int cpu)
{
	write_sysreg(0, osdlr_el1);
	write_sysreg(0, oslar_el1);
	isb();
	return 0;
}