#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kimage {int nr_segments; scalar_t__ start; TYPE_1__* segment; } ;
struct TYPE_2__ {scalar_t__ memsz; scalar_t__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void kexec_info(struct kimage *image)
{
        int i;
	printk("kexec information\n");
	for (i = 0; i < image->nr_segments; i++) {
	        printk("  segment[%d]: 0x%08x - 0x%08x (0x%08x)\n",
		       i,
		       (unsigned int)image->segment[i].mem,
		       (unsigned int)image->segment[i].mem +
				     image->segment[i].memsz,
		       (unsigned int)image->segment[i].memsz);
	}
	printk("  start     : 0x%08x\n\n", (unsigned int)image->start);
}