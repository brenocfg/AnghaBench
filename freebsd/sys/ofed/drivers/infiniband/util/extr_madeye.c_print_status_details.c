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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void print_status_details(u16 status)
{
	if (status & 0x0001)
		printk("               busy\n");
	if (status & 0x0002)
		printk("               redirection required\n");
	switch((status & 0x001C) >> 2) {
	case 1:
		printk("               bad version\n");
		break;
	case 2:
		printk("               method not supported\n");
		break;
	case 3:
		printk("               method/attribute combo not supported\n");
		break;
	case 7:
		printk("               invalid attribute/modifier value\n");
		break;
	}
}