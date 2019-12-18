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
 int /*<<< orphan*/  dtlk_port_lpc ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtlk_readable(void)
{
#ifdef TRACING
	printk(" dtlk_readable=%u@%u", inb_p(dtlk_port_lpc) != 0x7f, jiffies);
#endif
	return inb_p(dtlk_port_lpc) != 0x7f;
}