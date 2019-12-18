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
 int /*<<< orphan*/  CONFIG_BLK_DEV_INITRD ; 
 int /*<<< orphan*/  INITRD_SIZE ; 
 unsigned long INITRD_START ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rescue_initrd(unsigned long addr)
{
	if (!IS_ENABLED(CONFIG_BLK_DEV_INITRD))
		return;
	if (!INITRD_START || !INITRD_SIZE)
		return;
	if (addr <= INITRD_START)
		return;
	memmove((void *)addr, (void *)INITRD_START, INITRD_SIZE);
	INITRD_START = addr;
}