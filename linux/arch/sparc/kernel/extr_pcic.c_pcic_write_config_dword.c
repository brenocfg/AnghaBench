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
typedef  int /*<<< orphan*/  u32 ;
struct linux_pcic {scalar_t__ pcic_config_space_data; scalar_t__ pcic_config_space_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CMD (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct linux_pcic pcic0 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pcic_write_config_dword(unsigned int busno, unsigned int devfn,
    int where, u32 value)
{
	struct linux_pcic *pcic;
	unsigned long flags;

	pcic = &pcic0;

	local_irq_save(flags);
	writel(CONFIG_CMD(busno, devfn, where), pcic->pcic_config_space_addr);
	writel(value, pcic->pcic_config_space_data + (where&4));
	local_irq_restore(flags);
	return 0;
}