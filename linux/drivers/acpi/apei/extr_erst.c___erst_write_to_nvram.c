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
struct cper_record_header {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int __erst_write_to_nvram(const struct cper_record_header *record)
{
	/* do not print message, because printk is not safe for NMI */
	return -ENOSYS;
}