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
 scalar_t__ BOOT_ADDR ; 
 int /*<<< orphan*/  ENV_BOOTED_FILE ; 
 long callback_getenv (int /*<<< orphan*/ ,char*,int) ; 
 long callback_read (long,unsigned long,void*,long) ; 
 int /*<<< orphan*/  srm_printk (char*,char*) ; 

__attribute__((used)) static inline long load(long dev, unsigned long addr, unsigned long count)
{
	char bootfile[256];
	extern char _end;
	long result, boot_size = &_end - (char *) BOOT_ADDR;

	result = callback_getenv(ENV_BOOTED_FILE, bootfile, 255);
	if (result < 0)
		return result;
	result &= 255;
	bootfile[result] = '\0';
	if (result)
		srm_printk("Boot file specification (%s) not implemented\n",
		       bootfile);
	return callback_read(dev, count, (void *)addr, boot_size/512 + 1);
}