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
struct pd_unit {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pd_errs ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void pd_print_error(struct pd_unit *disk, char *msg, int status)
{
	int i;

	printk("%s: %s: status = 0x%x =", disk->name, msg, status);
	for (i = 0; i < ARRAY_SIZE(pd_errs); i++)
		if (status & (1 << i))
			printk(" %s", pd_errs[i]);
	printk("\n");
}