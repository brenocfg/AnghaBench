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
 int /*<<< orphan*/  err_print_prefix ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned int,unsigned long,char*) ; 

void
mchk_dump_mem(void *data, size_t length, char **annotation)
{
	unsigned long *ldata = data;
	size_t i;
	
	for (i = 0; (i * sizeof(*ldata)) < length; i++) {
		if (annotation && !annotation[i]) 
			annotation = NULL;
		printk("%s    %08x: %016lx    %s\n",
		       err_print_prefix,
		       (unsigned)(i * sizeof(*ldata)), ldata[i],
		       annotation ? annotation[i] : "");
	}
}