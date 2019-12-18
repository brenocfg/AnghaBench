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
 int /*<<< orphan*/  Index_Load_Tag_T ; 
 int /*<<< orphan*/  Index_Store_Tag_T ; 
 int /*<<< orphan*/  RM7K_CONF_TE ; 
 int /*<<< orphan*/  _stext ; 
 int /*<<< orphan*/  cache_op (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clear_c0_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  read_c0_taglo () ; 
 int /*<<< orphan*/  set_c0_config (int /*<<< orphan*/ ) ; 
 unsigned long tcache_size ; 
 int /*<<< orphan*/  write_c0_taghi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_taglo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __probe_tcache(void)
{
	unsigned long flags, addr, begin, end, pow2;

	begin = (unsigned long) &_stext;
	begin  &= ~((8 * 1024 * 1024) - 1);
	end = begin + (8 * 1024 * 1024);

	local_irq_save(flags);

	set_c0_config(RM7K_CONF_TE);

	/* Fill size-multiple lines with a valid tag */
	pow2 = (256 * 1024);
	for (addr = begin; addr <= end; addr = (begin + pow2)) {
		unsigned long *p = (unsigned long *) addr;
		__asm__ __volatile__("nop" : : "r" (*p));
		pow2 <<= 1;
	}

	/* Load first line with a 0 tag, to check after */
	write_c0_taglo(0);
	write_c0_taghi(0);
	cache_op(Index_Store_Tag_T, begin);

	/* Look for the wrap-around */
	pow2 = (512 * 1024);
	for (addr = begin + (512 * 1024); addr <= end; addr = begin + pow2) {
		cache_op(Index_Load_Tag_T, addr);
		if (!read_c0_taglo())
			break;
		pow2 <<= 1;
	}

	addr -= begin;
	tcache_size = addr;

	clear_c0_config(RM7K_CONF_TE);

	local_irq_restore(flags);
}