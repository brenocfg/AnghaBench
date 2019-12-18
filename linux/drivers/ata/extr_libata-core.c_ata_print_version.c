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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,struct device const*,char*,char const*) ; 

void ata_print_version(const struct device *dev, const char *version)
{
	dev_printk(KERN_DEBUG, dev, "version %s\n", version);
}