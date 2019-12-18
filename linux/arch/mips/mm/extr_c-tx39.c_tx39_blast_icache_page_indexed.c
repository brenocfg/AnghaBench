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
 unsigned long TX39_CONF_ICE ; 
 int /*<<< orphan*/  TX39_STOP_STREAMING () ; 
 int /*<<< orphan*/  blast_icache16_page_indexed (unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned long read_c0_conf () ; 
 int /*<<< orphan*/  write_c0_conf (unsigned long) ; 

__attribute__((used)) static inline void tx39_blast_icache_page_indexed(unsigned long addr)
{
	unsigned long flags, config;
	/* disable icache (set ICE#) */
	local_irq_save(flags);
	config = read_c0_conf();
	write_c0_conf(config & ~TX39_CONF_ICE);
	TX39_STOP_STREAMING();
	blast_icache16_page_indexed(addr);
	write_c0_conf(config);
	local_irq_restore(flags);
}